#include <gtest/gtest.h>
#include "fsm.hpp"
#include "memory.hpp"
#include "opcodes.hpp"
#include "reg.hpp"
#include <bitset>
#include <cstdint>

struct CpuFixture : ::testing::Test
{
	Memory mem;
	Reg<16> pc{std::bitset<16>(0xC000)};
	Reg<8> acc{std::bitset<8>(0)};
	Reg<8> x{std::bitset<8>(0)};
	Reg<8> y{std::bitset<8>(0)};
	Reg<8> sp{std::bitset<8>(0xFD)};
	Reg<8> status{std::bitset<8>(0b00000100)};
	fsm cpu{mem, pc, acc, x, y, sp, status};

	void SetUp() override
	{
		pc.updateValue(std::bitset<16>(0xC000));
		acc.updateValue(std::bitset<8>(0));
		x.updateValue(std::bitset<8>(0));
		y.updateValue(std::bitset<8>(0));
	}

	static uint16_t pcVal(Reg<16>& r) { return static_cast<uint16_t>(r.get().to_ulong()); }
	static uint8_t accVal(Reg<8>& r) { return static_cast<uint8_t>(r.get().to_ulong()); }

	// One full Fetch->Decode->Execute instruction.
	void runOneInstruction() { cpu.encode(); cpu.encode(); cpu.encode(); }
};

TEST_F(CpuFixture, LdaImmediateFF_SameAsBefore)
{
	mem[0xC000] = static_cast<std::byte>(0xA9);
	mem[0xC001] = static_cast<std::byte>(0xFF);

	cpu.encode(); // Fetch
	EXPECT_EQ(cpu.get_ir(), 0xA9);
	EXPECT_EQ(pcVal(pc), 0xC001);
	EXPECT_EQ(cpu.get_state(), fsm::State::Decode);

	cpu.encode(); // Decode: must fetch operand and advance PC
	EXPECT_EQ(cpu.get_decodedMode(), Opcodes::AddrMode::Immediate);
	EXPECT_EQ(cpu.get_decodedValue(), 0xFF);
	EXPECT_EQ(cpu.get_operandAddress(), 0xC001);
	EXPECT_EQ(cpu.get_decodedAddress(), 0xC001);
	EXPECT_EQ(pcVal(pc), 0xC002);
	EXPECT_EQ(cpu.get_state(), fsm::State::Execute);

	cpu.encode(); // Execute: must NOT move PC again, uses decoded value
	EXPECT_EQ(accVal(acc), 0xFF);
	EXPECT_TRUE(status.isFlagSet(Reg<8>::statusFlags::negative)); // 0xFF > 0x80
	EXPECT_FALSE(status.isFlagSet(Reg<8>::statusFlags::zero));
	EXPECT_EQ(pcVal(pc), 0xC002);
	EXPECT_EQ(cpu.get_state(), fsm::State::Fetch);
}

TEST_F(CpuFixture, LdaImmediateZero_SetsZeroFlag)
{
	mem[0xC000] = static_cast<std::byte>(0xA9);
	mem[0xC001] = static_cast<std::byte>(0x00);
	runOneInstruction();
	EXPECT_EQ(accVal(acc), 0x00);
	EXPECT_TRUE(status.isFlagSet(Reg<8>::statusFlags::zero));
	EXPECT_FALSE(status.isFlagSet(Reg<8>::statusFlags::negative));
	EXPECT_EQ(pcVal(pc), 0xC002);
}

TEST_F(CpuFixture, LdaImmediate80_PreservesOldNegativeBug)
{
	// Old code used `operand > 0x80`, so 0x80 did NOT set N.
	// Real 6502 would set N for 0x80. We preserve old behavior.
	mem[0xC000] = static_cast<std::byte>(0xA9);
	mem[0xC001] = static_cast<std::byte>(0x80);
	runOneInstruction();
	EXPECT_EQ(accVal(acc), 0x80);
	EXPECT_FALSE(status.isFlagSet(Reg<8>::statusFlags::negative));
}

TEST_F(CpuFixture, ImpliedClc_DecodeDoesNotAdvancePc)
{
	status.setFlag(Reg<8>::statusFlags::carry);
	mem[0xC000] = static_cast<std::byte>(0x18); // CLC
	cpu.encode(); // Fetch
	EXPECT_EQ(pcVal(pc), 0xC001);
	cpu.encode(); // Decode: implied, no operand
	EXPECT_EQ(cpu.get_decodedMode(), Opcodes::AddrMode::Implied);
	EXPECT_EQ(pcVal(pc), 0xC001);
	cpu.encode(); // Execute
	EXPECT_FALSE(status.isFlagSet(Reg<8>::statusFlags::carry));
	EXPECT_EQ(pcVal(pc), 0xC001);
}

TEST_F(CpuFixture, ImpliedSeiCli)
{
	mem[0xC000] = static_cast<std::byte>(0x78); // SEI
	mem[0xC001] = static_cast<std::byte>(0x58); // CLI
	runOneInstruction();
	EXPECT_TRUE(status.isFlagSet(Reg<8>::statusFlags::interruptDisable));
	EXPECT_EQ(pcVal(pc), 0xC001);
	runOneInstruction();
	EXPECT_FALSE(status.isFlagSet(Reg<8>::statusFlags::interruptDisable));
	EXPECT_EQ(pcVal(pc), 0xC002);
}

TEST_F(CpuFixture, NopIsSingleByte)
{
	mem[0xC000] = static_cast<std::byte>(0xEA);
	runOneInstruction();
	EXPECT_EQ(pcVal(pc), 0xC001);
}

TEST_F(CpuFixture, DecodeResolvesHandler)
{
	mem[0xC000] = static_cast<std::byte>(0xA9);
	mem[0xC001] = static_cast<std::byte>(0x42);
	cpu.encode();
	cpu.encode();
	EXPECT_NE(cpu.get_decodedHandler(), nullptr);
	Opcodes probe(mem, pc, acc, x, y, sp, status);
	EXPECT_EQ(cpu.get_decodedHandler(), probe[0xA9]);
}

TEST_F(CpuFixture, DecodeZeroPage_EffectiveAddress)
{
	// LDA zeropage (stub handler) still decodes addr/value for future use.
	mem[0xC000] = static_cast<std::byte>(0xA5);
	mem[0xC001] = static_cast<std::byte>(0x42);
	mem[0x0042] = static_cast<std::byte>(0x37);
	runOneInstruction();
	EXPECT_EQ(cpu.get_decodedMode(), Opcodes::AddrMode::ZeroPage);
	EXPECT_EQ(cpu.get_decodedAddress(), 0x0042);
	EXPECT_EQ(cpu.get_decodedValue(), 0x37);
	EXPECT_EQ(pcVal(pc), 0xC002);
}

TEST_F(CpuFixture, DecodeAbsoluteX_AddsX)
{
	mem[0xC000] = static_cast<std::byte>(0xBD); // LDA abs,X
	mem[0xC001] = static_cast<std::byte>(0x00);
	mem[0xC002] = static_cast<std::byte>(0x10);
	mem[0x1005] = static_cast<std::byte>(0x99);
	x.updateValue(std::bitset<8>(0x05));
	runOneInstruction();
	EXPECT_EQ(cpu.get_decodedMode(), Opcodes::AddrMode::AbsoluteX);
	EXPECT_EQ(cpu.get_decodedAddress(), 0x1005);
	EXPECT_EQ(cpu.get_decodedValue(), 0x99);
	EXPECT_EQ(pcVal(pc), 0xC003);
}

TEST_F(CpuFixture, DecodeRelative_ComputesTarget)
{
	mem[0xC000] = static_cast<std::byte>(0xD0); // BNE
	mem[0xC001] = static_cast<std::byte>(0xFE); // -2 -> target C000
	runOneInstruction();
	EXPECT_EQ(cpu.get_decodedMode(), Opcodes::AddrMode::Relative);
	EXPECT_EQ(pcVal(pc), 0xC002);
	EXPECT_EQ(cpu.get_decodedAddress(), 0xC000);
}

TEST_F(CpuFixture, DecodeIndirectX_WrapsZeroPage)
{
	mem[0xC000] = static_cast<std::byte>(0xA1); // LDA (ind,X)
	mem[0xC001] = static_cast<std::byte>(0x10);
	x.updateValue(std::bitset<8>(0x04)); // zp = 0x14
	mem[0x0014] = static_cast<std::byte>(0x34);
	mem[0x0015] = static_cast<std::byte>(0x12);
	mem[0x1234] = static_cast<std::byte>(0x77);
	runOneInstruction();
	EXPECT_EQ(cpu.get_decodedMode(), Opcodes::AddrMode::IndirectX);
	EXPECT_EQ(cpu.get_decodedAddress(), 0x1234);
	EXPECT_EQ(cpu.get_decodedValue(), 0x77);
	EXPECT_EQ(pcVal(pc), 0xC002);
}

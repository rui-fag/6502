#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include "memory.hpp"
#include "reg.hpp"

class Opcodes
{
	public:
		using Handler = void (Opcodes::*)();
		enum class AddrMode : std::uint8_t
		{
			Implied,
			Accumulator,
			Immediate,
			ZeroPage,
			ZeroPageX,
			ZeroPageY,
			Absolute,
			AbsoluteX,
			AbsoluteY,
			Indirect,
			IndirectX,
			IndirectY,
			Relative
		};
	private:
		static constexpr std::size_t kNumOpcodes = 256;
		static const std::array<Handler, kNumOpcodes> opcodes;
		static const std::array<AddrMode, kNumOpcodes> addrModes;
		Memory& mem_;
		Reg<16>& pc_;
		Reg<8>& acc_;
		Reg<8>& regX_;
		Reg<8>& regY_;
		Reg<8>& sp_;
		Reg<8>& status_;
		std::uint8_t decodedValue_{0};
		std::uint16_t decodedAddress_{0};
		std::uint16_t operandAddress_{0};
	public:
		explicit Opcodes(Memory& mem, Reg<16>& pc, Reg<8>& acc, Reg<8>& x, Reg<8>& y, Reg<8>& sp, Reg<8>& status)
			: mem_(mem), pc_(pc), acc_(acc), regX_(x), regY_(y), sp_(sp), status_(status) {}
		constexpr void dispatch(std::uint8_t opcode) { (this->*opcodes[opcode])(); }
		constexpr void dispatchHandler(Handler h) { (this->*h)(); }
		constexpr Handler operator[](std::uint8_t opcode) const { return opcodes[opcode]; }
		static constexpr AddrMode addressingMode(std::uint8_t opcode) { return addrModes[opcode]; }
		static constexpr std::size_t operandBytes(AddrMode mode)
		{
			switch (mode)
			{
				case AddrMode::Immediate:
				case AddrMode::ZeroPage:
				case AddrMode::ZeroPageX:
				case AddrMode::ZeroPageY:
				case AddrMode::IndirectX:
				case AddrMode::IndirectY:
				case AddrMode::Relative:
					return 1;
				case AddrMode::Absolute:
				case AddrMode::AbsoluteX:
				case AddrMode::AbsoluteY:
				case AddrMode::Indirect:
					return 2;
				case AddrMode::Implied:
				case AddrMode::Accumulator:
				default:
					return 0;
			}
		}
		static constexpr std::size_t operandBytes(std::uint8_t opcode) { return operandBytes(addressingMode(opcode)); }
		void setDecoded(std::uint8_t value, std::uint16_t effectiveAddress, std::uint16_t operandAddress)
		{
			decodedValue_ = value;
			decodedAddress_ = effectiveAddress;
			operandAddress_ = operandAddress;
		}
		constexpr std::uint8_t decodedValue(void) const { return decodedValue_; }
		constexpr std::uint16_t decodedAddress(void) const { return decodedAddress_; }
		constexpr std::uint16_t operandAddress(void) const { return operandAddress_; }
	public:
	// ADC - Add with Carry (8 modes)
		void ADC_IMMEDIATE(void);   // 0x69
		void ADC_ZEROPAGE(void);    // 0x65
		void ADC_ZEROPAGE_X(void);  // 0x75
		void ADC_ABSOLUTE(void);    // 0x6D
		void ADC_ABSOLUTE_X(void);  // 0x7D
		void ADC_ABSOLUTE_Y(void);  // 0x79
		void ADC_INDIRECT_X(void);  // 0x61 (Indexed Indirect)
		void ADC_INDIRECT_Y(void);  // 0x71 (Indirect Indexed)

		// AND - Logical AND (8 modes)
		void AND_IMMEDIATE(void);   // 0x29
		void AND_ZEROPAGE(void);    // 0x25
		void AND_ZEROPAGE_X(void);  // 0x35
		void AND_ABSOLUTE(void);    // 0x2D
		void AND_ABSOLUTE_X(void);  // 0x3D
		void AND_ABSOLUTE_Y(void);  // 0x39
		void AND_INDIRECT_X(void);  // 0x21
		void AND_INDIRECT_Y(void);  // 0x31

		// ASL - Arithmetic Shift Left (5 modes)
		void ASL_ACCUMULATOR(void); // 0x0A
		void ASL_ZEROPAGE(void);    // 0x06
		void ASL_ZEROPAGE_X(void);  // 0x16
		void ASL_ABSOLUTE(void);    // 0x0E
		void ASL_ABSOLUTE_X(void);  // 0x1E

		// Branches (Relative, 1 mode each)
		void BCC_RELATIVE(void);    // 0x90
		void BCS_RELATIVE(void);    // 0xB0
		void BEQ_RELATIVE(void);    // 0xF0
		void BMI_RELATIVE(void);    // 0x30
		void BNE_RELATIVE(void);    // 0xD0
		void BPL_RELATIVE(void);    // 0x10
		void BVC_RELATIVE(void);    // 0x50
		void BVS_RELATIVE(void);    // 0x70

		// BIT - Bit Test (2 modes)
		void BIT_ZEROPAGE(void);    // 0x24
		void BIT_ABSOLUTE(void);    // 0x2C

		// BRK - Force Interrupt (Implied)
		void BRK_IMPLIED(void);     // 0x00

		// Flags - Clear (Implied, 1 mode each)
		void CLC_IMPLIED(void);     // 0x18
		void CLD_IMPLIED(void);     // 0xD8
		void CLI_IMPLIED(void);     // 0x58
		void CLV_IMPLIED(void);     // 0xB8

		// CMP - Compare Accumulator (8 modes)
		void CMP_IMMEDIATE(void);   // 0xC9
		void CMP_ZEROPAGE(void);    // 0xC5
		void CMP_ZEROPAGE_X(void);  // 0xD5
		void CMP_ABSOLUTE(void);    // 0xCD
		void CMP_ABSOLUTE_X(void);  // 0xDD
		void CMP_ABSOLUTE_Y(void);  // 0xD9
		void CMP_INDIRECT_X(void);  // 0xC1
		void CMP_INDIRECT_Y(void);  // 0xD1

		// CPX - Compare X Register (3 modes)
		void CPX_IMMEDIATE(void);   // 0xE0
		void CPX_ZEROPAGE(void);    // 0xE4
		void CPX_ABSOLUTE(void);    // 0xEC

		// CPY - Compare Y Register (3 modes)
		void CPY_IMMEDIATE(void);   // 0xC0
		void CPY_ZEROPAGE(void);    // 0xC4
		void CPY_ABSOLUTE(void);    // 0xCC

		// DEC - Decrement Memory (4 modes)
		void DEC_ZEROPAGE(void);    // 0xC6
		void DEC_ZEROPAGE_X(void);  // 0xD6
		void DEC_ABSOLUTE(void);    // 0xCE
		void DEC_ABSOLUTE_X(void);  // 0xDE

		// Decrement Registers (Implied)
		void DEX_IMPLIED(void);     // 0xCA
		void DEY_IMPLIED(void);     // 0x88

		// EOR - Exclusive OR (8 modes)
		void EOR_IMMEDIATE(void);   // 0x49
		void EOR_ZEROPAGE(void);    // 0x45
		void EOR_ZEROPAGE_X(void);  // 0x55
		void EOR_ABSOLUTE(void);    // 0x4D
		void EOR_ABSOLUTE_X(void);  // 0x5D
		void EOR_ABSOLUTE_Y(void);  // 0x59
		void EOR_INDIRECT_X(void);  // 0x41
		void EOR_INDIRECT_Y(void);  // 0x51

		// INC - Increment Memory (4 modes)
		void INC_ZEROPAGE(void);    // 0xE6
		void INC_ZEROPAGE_X(void);  // 0xF6
		void INC_ABSOLUTE(void);    // 0xEE
		void INC_ABSOLUTE_X(void);  // 0xFE

		// Increment Registers (Implied)
		void INX_IMPLIED(void);     // 0xE8
		void INY_IMPLIED(void);     // 0xC8

		// JMP - Jump (2 modes)
		void JMP_ABSOLUTE(void);    // 0x4C
		void JMP_INDIRECT(void);    // 0x6C

		// JSR - Jump to Subroutine (Absolute only)
		void JSR_ABSOLUTE(void);    // 0x20

		// LDA - Load Accumulator (8 modes)
		void LDA_IMMEDIATE(void);   // 0xA9
		void LDA_ZEROPAGE(void);    // 0xA5
		void LDA_ZEROPAGE_X(void);  // 0xB5
		void LDA_ABSOLUTE(void);    // 0xAD
		void LDA_ABSOLUTE_X(void);  // 0xBD
		void LDA_ABSOLUTE_Y(void);  // 0xB9
		void LDA_INDIRECT_X(void);  // 0xA1
		void LDA_INDIRECT_Y(void);  // 0xB1

		// LDX - Load X Register (5 modes)
		void LDX_IMMEDIATE(void);   // 0xA2
		void LDX_ZEROPAGE(void);    // 0xA6
		void LDX_ZEROPAGE_Y(void);  // 0xB6
		void LDX_ABSOLUTE(void);    // 0xAE
		void LDX_ABSOLUTE_Y(void);  // 0xBE

		// LDY - Load Y Register (5 modes)
		void LDY_IMMEDIATE(void);   // 0xA0
		void LDY_ZEROPAGE(void);    // 0xA4
		void LDY_ZEROPAGE_X(void);  // 0xB4
		void LDY_ABSOLUTE(void);    // 0xAC
		void LDY_ABSOLUTE_X(void);  // 0xBC

		// LSR - Logical Shift Right (5 modes)
		void LSR_ACCUMULATOR(void); // 0x4A
		void LSR_ZEROPAGE(void);    // 0x46
		void LSR_ZEROPAGE_X(void);  // 0x56
		void LSR_ABSOLUTE(void);    // 0x4E
		void LSR_ABSOLUTE_X(void);  // 0x5E

		// NOP - No Operation (Implied)
		void NOP_IMPLIED(void);     // 0xEA

		// ORA - Logical OR (8 modes)
		void ORA_IMMEDIATE(void);   // 0x09
		void ORA_ZEROPAGE(void);    // 0x05
		void ORA_ZEROPAGE_X(void);  // 0x15
		void ORA_ABSOLUTE(void);    // 0x0D
		void ORA_ABSOLUTE_X(void);  // 0x1D
		void ORA_ABSOLUTE_Y(void);  // 0x19
		void ORA_INDIRECT_X(void);  // 0x01
		void ORA_INDIRECT_Y(void);  // 0x11

		// Stack / Status (Implied, 1 mode each)
		void PHA_IMPLIED(void);     // 0x48
		void PHP_IMPLIED(void);     // 0x08
		void PLA_IMPLIED(void);     // 0x68
		void PLP_IMPLIED(void);     // 0x28

		// ROL - Rotate Left (5 modes)
		void ROL_ACCUMULATOR(void); // 0x2A
		void ROL_ZEROPAGE(void);    // 0x26
		void ROL_ZEROPAGE_X(void);  // 0x36
		void ROL_ABSOLUTE(void);    // 0x2E
		void ROL_ABSOLUTE_X(void);  // 0x3E

		// ROR - Rotate Right (5 modes)
		void ROR_ACCUMULATOR(void); // 0x6A
		void ROR_ZEROPAGE(void);    // 0x66
		void ROR_ZEROPAGE_X(void);  // 0x76
		void ROR_ABSOLUTE(void);    // 0x6E
		void ROR_ABSOLUTE_X(void);  // 0x7E

		// Returns from Interrupt / Subroutine (Implied)
		void RTI_IMPLIED(void);     // 0x40
		void RTS_IMPLIED(void);     // 0x60

		// SBC - Subtract with Carry (8 modes)
		void SBC_IMMEDIATE(void);   // 0xE9
		void SBC_ZEROPAGE(void);    // 0xE5
		void SBC_ZEROPAGE_X(void);  // 0xF5
		void SBC_ABSOLUTE(void);    // 0xED
		void SBC_ABSOLUTE_X(void);  // 0xFD
		void SBC_ABSOLUTE_Y(void);  // 0xF9
		void SBC_INDIRECT_X(void);  // 0xE1
		void SBC_INDIRECT_Y(void);  // 0xF1

		// Flags - Set (Implied, 1 mode each)
		void SEC_IMPLIED(void);     // 0x38
		void SED_IMPLIED(void);     // 0xF8
		void SEI_IMPLIED(void);     // 0x78

		// STA - Store Accumulator (7 modes, no Immediate)
		void STA_ZEROPAGE(void);    // 0x85
		void STA_ZEROPAGE_X(void);  // 0x95
		void STA_ABSOLUTE(void);    // 0x8D
		void STA_ABSOLUTE_X(void);  // 0x9D
		void STA_ABSOLUTE_Y(void);  // 0x99
		void STA_INDIRECT_X(void);  // 0x81
		void STA_INDIRECT_Y(void);  // 0x91

		// STX - Store X Register (3 modes)
		void STX_ZEROPAGE(void);    // 0x86
		void STX_ZEROPAGE_Y(void);  // 0x96
		void STX_ABSOLUTE(void);    // 0x8E

		// STY - Store Y Register (3 modes)
		void STY_ZEROPAGE(void);    // 0x84
		void STY_ZEROPAGE_X(void);  // 0x94
		void STY_ABSOLUTE(void);    // 0x8C

		// Transfers (Implied, 1 mode each)
		void TAX_IMPLIED(void);     // 0xAA
		void TAY_IMPLIED(void);     // 0xA8
		void TSX_IMPLIED(void);     // 0xBA
		void TXA_IMPLIED(void);     // 0x8A
		void TXS_IMPLIED(void);     // 0x9A
		void TYA_IMPLIED(void);     // 0x98
};

inline constexpr std::array<Opcodes::Handler, Opcodes::kNumOpcodes> Opcodes::opcodes = []
{
	std::array<Opcodes::Handler, Opcodes::kNumOpcodes> table{};
	table.fill(&Opcodes::NOP_IMPLIED);
	table[0x00] = &Opcodes::BRK_IMPLIED;
	table[0x01] = &Opcodes::ORA_INDIRECT_X;
	table[0x05] = &Opcodes::ORA_ZEROPAGE;
	table[0x06] = &Opcodes::ASL_ZEROPAGE;
	table[0x08] = &Opcodes::PHP_IMPLIED;
	table[0x09] = &Opcodes::ORA_IMMEDIATE;
	table[0x0A] = &Opcodes::ASL_ACCUMULATOR;
	table[0x0D] = &Opcodes::ORA_ABSOLUTE;
	table[0x0E] = &Opcodes::ASL_ABSOLUTE;
	table[0x10] = &Opcodes::BPL_RELATIVE;
	table[0x11] = &Opcodes::ORA_INDIRECT_Y;
	table[0x15] = &Opcodes::ORA_ZEROPAGE_X;
	table[0x16] = &Opcodes::ASL_ZEROPAGE_X;
	table[0x18] = &Opcodes::CLC_IMPLIED;
	table[0x19] = &Opcodes::ORA_ABSOLUTE_Y;
	table[0x1D] = &Opcodes::ORA_ABSOLUTE_X;
	table[0x1E] = &Opcodes::ASL_ABSOLUTE_X;
	table[0x20] = &Opcodes::JSR_ABSOLUTE;
	table[0x21] = &Opcodes::AND_INDIRECT_X;
	table[0x24] = &Opcodes::BIT_ZEROPAGE;
	table[0x25] = &Opcodes::AND_ZEROPAGE;
	table[0x26] = &Opcodes::ROL_ZEROPAGE;
	table[0x28] = &Opcodes::PLP_IMPLIED;
	table[0x29] = &Opcodes::AND_IMMEDIATE;
	table[0x2A] = &Opcodes::ROL_ACCUMULATOR;
	table[0x2C] = &Opcodes::BIT_ABSOLUTE;
	table[0x2D] = &Opcodes::AND_ABSOLUTE;
	table[0x2E] = &Opcodes::ROL_ABSOLUTE;
	table[0x30] = &Opcodes::BMI_RELATIVE;
	table[0x31] = &Opcodes::AND_INDIRECT_Y;
	table[0x35] = &Opcodes::AND_ZEROPAGE_X;
	table[0x36] = &Opcodes::ROL_ZEROPAGE_X;
	table[0x38] = &Opcodes::SEC_IMPLIED;
	table[0x39] = &Opcodes::AND_ABSOLUTE_Y;
	table[0x3D] = &Opcodes::AND_ABSOLUTE_X;
	table[0x3E] = &Opcodes::ROL_ABSOLUTE_X;
	table[0x40] = &Opcodes::RTI_IMPLIED;
	table[0x41] = &Opcodes::EOR_INDIRECT_X;
	table[0x45] = &Opcodes::EOR_ZEROPAGE;
	table[0x46] = &Opcodes::LSR_ZEROPAGE;
	table[0x48] = &Opcodes::PHA_IMPLIED;
	table[0x49] = &Opcodes::EOR_IMMEDIATE;
	table[0x4A] = &Opcodes::LSR_ACCUMULATOR;
	table[0x4C] = &Opcodes::JMP_ABSOLUTE;
	table[0x4D] = &Opcodes::EOR_ABSOLUTE;
	table[0x4E] = &Opcodes::LSR_ABSOLUTE;
	table[0x50] = &Opcodes::BVC_RELATIVE;
	table[0x51] = &Opcodes::EOR_INDIRECT_Y;
	table[0x55] = &Opcodes::EOR_ZEROPAGE_X;
	table[0x56] = &Opcodes::LSR_ZEROPAGE_X;
	table[0x58] = &Opcodes::CLI_IMPLIED;
	table[0x59] = &Opcodes::EOR_ABSOLUTE_Y;
	table[0x5D] = &Opcodes::EOR_ABSOLUTE_X;
	table[0x5E] = &Opcodes::LSR_ABSOLUTE_X;
	table[0x60] = &Opcodes::RTS_IMPLIED;
	table[0x61] = &Opcodes::ADC_INDIRECT_X;
	table[0x65] = &Opcodes::ADC_ZEROPAGE;
	table[0x66] = &Opcodes::ROR_ZEROPAGE;
	table[0x68] = &Opcodes::PLA_IMPLIED;
	table[0x69] = &Opcodes::ADC_IMMEDIATE;
	table[0x6A] = &Opcodes::ROR_ACCUMULATOR;
	table[0x6C] = &Opcodes::JMP_INDIRECT;
	table[0x6D] = &Opcodes::ADC_ABSOLUTE;
	table[0x6E] = &Opcodes::ROR_ABSOLUTE;
	table[0x70] = &Opcodes::BVS_RELATIVE;
	table[0x71] = &Opcodes::ADC_INDIRECT_Y;
	table[0x75] = &Opcodes::ADC_ZEROPAGE_X;
	table[0x76] = &Opcodes::ROR_ZEROPAGE_X;
	table[0x78] = &Opcodes::SEI_IMPLIED;
	table[0x79] = &Opcodes::ADC_ABSOLUTE_Y;
	table[0x7D] = &Opcodes::ADC_ABSOLUTE_X;
	table[0x7E] = &Opcodes::ROR_ABSOLUTE_X;
	table[0x81] = &Opcodes::STA_INDIRECT_X;
	table[0x84] = &Opcodes::STY_ZEROPAGE;
	table[0x85] = &Opcodes::STA_ZEROPAGE;
	table[0x86] = &Opcodes::STX_ZEROPAGE;
	table[0x88] = &Opcodes::DEY_IMPLIED;
	table[0x8A] = &Opcodes::TXA_IMPLIED;
	table[0x8C] = &Opcodes::STY_ABSOLUTE;
	table[0x8D] = &Opcodes::STA_ABSOLUTE;
	table[0x8E] = &Opcodes::STX_ABSOLUTE;
	table[0x90] = &Opcodes::BCC_RELATIVE;
	table[0x91] = &Opcodes::STA_INDIRECT_Y;
	table[0x94] = &Opcodes::STY_ZEROPAGE_X;
	table[0x95] = &Opcodes::STA_ZEROPAGE_X;
	table[0x96] = &Opcodes::STX_ZEROPAGE_Y;
	table[0x98] = &Opcodes::TYA_IMPLIED;
	table[0x99] = &Opcodes::STA_ABSOLUTE_Y;
	table[0x9A] = &Opcodes::TXS_IMPLIED;
	table[0x9D] = &Opcodes::STA_ABSOLUTE_X;
	table[0xA0] = &Opcodes::LDY_IMMEDIATE;
	table[0xA1] = &Opcodes::LDA_INDIRECT_X;
	table[0xA2] = &Opcodes::LDX_IMMEDIATE;
	table[0xA4] = &Opcodes::LDY_ZEROPAGE;
	table[0xA5] = &Opcodes::LDA_ZEROPAGE;
	table[0xA6] = &Opcodes::LDX_ZEROPAGE;
	table[0xA8] = &Opcodes::TAY_IMPLIED;
	table[0xA9] = &Opcodes::LDA_IMMEDIATE;
	table[0xAA] = &Opcodes::TAX_IMPLIED;
	table[0xAC] = &Opcodes::LDY_ABSOLUTE;
	table[0xAD] = &Opcodes::LDA_ABSOLUTE;
	table[0xAE] = &Opcodes::LDX_ABSOLUTE;
	table[0xB0] = &Opcodes::BCS_RELATIVE;
	table[0xB1] = &Opcodes::LDA_INDIRECT_Y;
	table[0xB4] = &Opcodes::LDY_ZEROPAGE_X;
	table[0xB5] = &Opcodes::LDA_ZEROPAGE_X;
	table[0xB6] = &Opcodes::LDX_ZEROPAGE_Y;
	table[0xB8] = &Opcodes::CLV_IMPLIED;
	table[0xB9] = &Opcodes::LDA_ABSOLUTE_Y;
	table[0xBA] = &Opcodes::TSX_IMPLIED;
	table[0xBC] = &Opcodes::LDY_ABSOLUTE_X;
	table[0xBD] = &Opcodes::LDA_ABSOLUTE_X;
	table[0xBE] = &Opcodes::LDX_ABSOLUTE_Y;
	table[0xC0] = &Opcodes::CPY_IMMEDIATE;
	table[0xC1] = &Opcodes::CMP_INDIRECT_X;
	table[0xC4] = &Opcodes::CPY_ZEROPAGE;
	table[0xC5] = &Opcodes::CMP_ZEROPAGE;
	table[0xC6] = &Opcodes::DEC_ZEROPAGE;
	table[0xC8] = &Opcodes::INY_IMPLIED;
	table[0xC9] = &Opcodes::CMP_IMMEDIATE;
	table[0xCA] = &Opcodes::DEX_IMPLIED;
	table[0xCC] = &Opcodes::CPY_ABSOLUTE;
	table[0xCD] = &Opcodes::CMP_ABSOLUTE;
	table[0xCE] = &Opcodes::DEC_ABSOLUTE;
	table[0xD0] = &Opcodes::BNE_RELATIVE;
	table[0xD1] = &Opcodes::CMP_INDIRECT_Y;
	table[0xD5] = &Opcodes::CMP_ZEROPAGE_X;
	table[0xD6] = &Opcodes::DEC_ZEROPAGE_X;
	table[0xD8] = &Opcodes::CLD_IMPLIED;
	table[0xD9] = &Opcodes::CMP_ABSOLUTE_Y;
	table[0xDD] = &Opcodes::CMP_ABSOLUTE_X;
	table[0xDE] = &Opcodes::DEC_ABSOLUTE_X;
	table[0xE0] = &Opcodes::CPX_IMMEDIATE;
	table[0xE1] = &Opcodes::SBC_INDIRECT_X;
	table[0xE4] = &Opcodes::CPX_ZEROPAGE;
	table[0xE5] = &Opcodes::SBC_ZEROPAGE;
	table[0xE6] = &Opcodes::INC_ZEROPAGE;
	table[0xE8] = &Opcodes::INX_IMPLIED;
	table[0xE9] = &Opcodes::SBC_IMMEDIATE;
	table[0xEA] = &Opcodes::NOP_IMPLIED;
	table[0xEC] = &Opcodes::CPX_ABSOLUTE;
	table[0xED] = &Opcodes::SBC_ABSOLUTE;
	table[0xEE] = &Opcodes::INC_ABSOLUTE;
	table[0xF0] = &Opcodes::BEQ_RELATIVE;
	table[0xF1] = &Opcodes::SBC_INDIRECT_Y;
	table[0xF5] = &Opcodes::SBC_ZEROPAGE_X;
	table[0xF6] = &Opcodes::INC_ZEROPAGE_X;
	table[0xF8] = &Opcodes::SED_IMPLIED;
	table[0xF9] = &Opcodes::SBC_ABSOLUTE_Y;
	table[0xFD] = &Opcodes::SBC_ABSOLUTE_X;
	table[0xFE] = &Opcodes::INC_ABSOLUTE_X;
	return table;
}();

inline constexpr std::array<Opcodes::AddrMode, Opcodes::kNumOpcodes> Opcodes::addrModes = []
{
	using M = Opcodes::AddrMode;
	std::array<M, Opcodes::kNumOpcodes> table{};
	table.fill(M::Implied);
	table[0x01] = M::IndirectX;
	table[0x05] = M::ZeroPage;
	table[0x06] = M::ZeroPage;
	table[0x09] = M::Immediate;
	table[0x0A] = M::Accumulator;
	table[0x0D] = M::Absolute;
	table[0x0E] = M::Absolute;
	table[0x10] = M::Relative;
	table[0x11] = M::IndirectY;
	table[0x15] = M::ZeroPageX;
	table[0x16] = M::ZeroPageX;
	table[0x19] = M::AbsoluteY;
	table[0x1D] = M::AbsoluteX;
	table[0x1E] = M::AbsoluteX;
	table[0x20] = M::Absolute;
	table[0x21] = M::IndirectX;
	table[0x24] = M::ZeroPage;
	table[0x25] = M::ZeroPage;
	table[0x26] = M::ZeroPage;
	table[0x29] = M::Immediate;
	table[0x2A] = M::Accumulator;
	table[0x2C] = M::Absolute;
	table[0x2D] = M::Absolute;
	table[0x2E] = M::Absolute;
	table[0x30] = M::Relative;
	table[0x31] = M::IndirectY;
	table[0x35] = M::ZeroPageX;
	table[0x36] = M::ZeroPageX;
	table[0x39] = M::AbsoluteY;
	table[0x3D] = M::AbsoluteX;
	table[0x3E] = M::AbsoluteX;
	table[0x41] = M::IndirectX;
	table[0x45] = M::ZeroPage;
	table[0x46] = M::ZeroPage;
	table[0x49] = M::Immediate;
	table[0x4A] = M::Accumulator;
	table[0x4C] = M::Absolute;
	table[0x4D] = M::Absolute;
	table[0x4E] = M::Absolute;
	table[0x50] = M::Relative;
	table[0x51] = M::IndirectY;
	table[0x55] = M::ZeroPageX;
	table[0x56] = M::ZeroPageX;
	table[0x59] = M::AbsoluteY;
	table[0x5D] = M::AbsoluteX;
	table[0x5E] = M::AbsoluteX;
	table[0x61] = M::IndirectX;
	table[0x65] = M::ZeroPage;
	table[0x66] = M::ZeroPage;
	table[0x69] = M::Immediate;
	table[0x6A] = M::Accumulator;
	table[0x6C] = M::Indirect;
	table[0x6D] = M::Absolute;
	table[0x6E] = M::Absolute;
	table[0x70] = M::Relative;
	table[0x71] = M::IndirectY;
	table[0x75] = M::ZeroPageX;
	table[0x76] = M::ZeroPageX;
	table[0x79] = M::AbsoluteY;
	table[0x7D] = M::AbsoluteX;
	table[0x7E] = M::AbsoluteX;
	table[0x81] = M::IndirectX;
	table[0x84] = M::ZeroPage;
	table[0x85] = M::ZeroPage;
	table[0x86] = M::ZeroPage;
	table[0x8C] = M::Absolute;
	table[0x8D] = M::Absolute;
	table[0x8E] = M::Absolute;
	table[0x90] = M::Relative;
	table[0x91] = M::IndirectY;
	table[0x94] = M::ZeroPageX;
	table[0x95] = M::ZeroPageX;
	table[0x96] = M::ZeroPageY;
	table[0x99] = M::AbsoluteY;
	table[0x9D] = M::AbsoluteX;
	table[0xA0] = M::Immediate;
	table[0xA1] = M::IndirectX;
	table[0xA2] = M::Immediate;
	table[0xA4] = M::ZeroPage;
	table[0xA5] = M::ZeroPage;
	table[0xA6] = M::ZeroPage;
	table[0xA9] = M::Immediate;
	table[0xAC] = M::Absolute;
	table[0xAD] = M::Absolute;
	table[0xAE] = M::Absolute;
	table[0xB0] = M::Relative;
	table[0xB1] = M::IndirectY;
	table[0xB4] = M::ZeroPageX;
	table[0xB5] = M::ZeroPageX;
	table[0xB6] = M::ZeroPageY;
	table[0xB9] = M::AbsoluteY;
	table[0xBC] = M::AbsoluteX;
	table[0xBD] = M::AbsoluteX;
	table[0xBE] = M::AbsoluteY;
	table[0xC0] = M::Immediate;
	table[0xC1] = M::IndirectX;
	table[0xC4] = M::ZeroPage;
	table[0xC5] = M::ZeroPage;
	table[0xC6] = M::ZeroPage;
	table[0xC9] = M::Immediate;
	table[0xCC] = M::Absolute;
	table[0xCD] = M::Absolute;
	table[0xCE] = M::Absolute;
	table[0xD0] = M::Relative;
	table[0xD1] = M::IndirectY;
	table[0xD5] = M::ZeroPageX;
	table[0xD6] = M::ZeroPageX;
	table[0xD9] = M::AbsoluteY;
	table[0xDD] = M::AbsoluteX;
	table[0xDE] = M::AbsoluteX;
	table[0xE0] = M::Immediate;
	table[0xE1] = M::IndirectX;
	table[0xE4] = M::ZeroPage;
	table[0xE5] = M::ZeroPage;
	table[0xE6] = M::ZeroPage;
	table[0xE9] = M::Immediate;
	table[0xEC] = M::Absolute;
	table[0xED] = M::Absolute;
	table[0xEE] = M::Absolute;
	table[0xF0] = M::Relative;
	table[0xF1] = M::IndirectY;
	table[0xF5] = M::ZeroPageX;
	table[0xF6] = M::ZeroPageX;
	table[0xF9] = M::AbsoluteY;
	table[0xFD] = M::AbsoluteX;
	table[0xFE] = M::AbsoluteX;
	return table;
}();

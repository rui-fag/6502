#include "fsm.hpp"
#include <cstddef>
#include <iostream>
#include <expected>
#include <iomanip>

fsm::fsm(Memory& mem_, Reg<16>& pc_, Reg<8>& acc_, Reg<8>& x_, Reg<8>& y_, Reg<8>& sp_, Reg<8>& status_)
    : mem(mem_),
      pc(pc_),
      acc(acc_),
      regX(x_),
      regY(y_),
      sp(sp_),
      status(status_),
      ir(0),
	  _opcode(mem, pc, acc, regX, regY, sp, status),
      state(State::Fetch),
      states{
          [this] { return fetch(); },
          [this] { return decode(); },
          [this] { return execute(); }
      }
{
}


void fsm::encode(void)
	pre (std::to_underlying(state) < states.size())
{
	state = states[std::to_underlying(state)]();
}

fsm::State fsm::fetch(void)
{
	logRegisters("fetch start");
	uint16_t pcVal = static_cast<uint16_t>(pc.get().to_ulong());
	ir = std::to_integer<uint8_t>(mem[pcVal]);
	pc.updateValue(std::bitset<16>(static_cast<unsigned long>(pcVal + 1)));
	std::cout  << "fetch\n";
	return State::Decode;
}

fsm::State fsm::decode(void)
{
	decodedHandler = _opcode[ir];
	decodedMode = Opcodes::addressingMode(ir);
	uint16_t pcVal = static_cast<uint16_t>(pc.get().to_ulong());
	uint8_t regXVal = static_cast<uint8_t>(regX.get().to_ulong());
	uint8_t regYVal = static_cast<uint8_t>(regY.get().to_ulong());

	decodedValue = 0;
	decodedAddress = 0;
	operandAddress = pcVal;

	auto readByte = [this](uint16_t addr) {
		return std::to_integer<uint8_t>(mem[addr]);
	};
	auto readAddrZP = [this, readByte](uint8_t zp) {
		uint8_t lo = readByte(zp);
		uint8_t hi = readByte(static_cast<uint8_t>(zp + 1));
		return static_cast<uint16_t>(lo) | (static_cast<uint16_t>(hi) << 8);
	};

	switch (decodedMode)
	{
		case Opcodes::AddrMode::Implied:
		case Opcodes::AddrMode::Accumulator:
			break;
		case Opcodes::AddrMode::Immediate:
		{
			decodedValue = readByte(pcVal);
			decodedAddress = pcVal;
			pc.updateValue(std::bitset<16>(static_cast<unsigned long>(pcVal + 1)));
			break;
		}
		case Opcodes::AddrMode::ZeroPage:
		{
			uint8_t zp = readByte(pcVal);
			pc.updateValue(std::bitset<16>(static_cast<unsigned long>(pcVal + 1)));
			decodedAddress = zp;
			decodedValue = readByte(decodedAddress);
			break;
		}
		case Opcodes::AddrMode::ZeroPageX:
		{
			uint8_t base = readByte(pcVal);
			pc.updateValue(std::bitset<16>(static_cast<unsigned long>(pcVal + 1)));
			decodedAddress = static_cast<uint8_t>(base + regXVal);
			decodedValue = readByte(decodedAddress);
			break;
		}
		case Opcodes::AddrMode::ZeroPageY:
		{
			uint8_t base = readByte(pcVal);
			pc.updateValue(std::bitset<16>(static_cast<unsigned long>(pcVal + 1)));
			decodedAddress = static_cast<uint8_t>(base + regYVal);
			decodedValue = readByte(decodedAddress);
			break;
		}
		case Opcodes::AddrMode::Absolute:
		{
			uint8_t lo = readByte(pcVal);
			uint8_t hi = readByte(static_cast<uint16_t>(pcVal + 1));
			pc.updateValue(std::bitset<16>(static_cast<unsigned long>(pcVal + 2)));
			decodedAddress = static_cast<uint16_t>(lo) | (static_cast<uint16_t>(hi) << 8);
			decodedValue = readByte(decodedAddress);
			break;
		}
		case Opcodes::AddrMode::AbsoluteX:
		{
			uint8_t lo = readByte(pcVal);
			uint8_t hi = readByte(static_cast<uint16_t>(pcVal + 1));
			pc.updateValue(std::bitset<16>(static_cast<unsigned long>(pcVal + 2)));
			uint16_t base = static_cast<uint16_t>(lo) | (static_cast<uint16_t>(hi) << 8);
			decodedAddress = static_cast<uint16_t>(base + regXVal);
			decodedValue = readByte(decodedAddress);
			break;
		}
		case Opcodes::AddrMode::AbsoluteY:
		{
			uint8_t lo = readByte(pcVal);
			uint8_t hi = readByte(static_cast<uint16_t>(pcVal + 1));
			pc.updateValue(std::bitset<16>(static_cast<unsigned long>(pcVal + 2)));
			uint16_t base = static_cast<uint16_t>(lo) | (static_cast<uint16_t>(hi) << 8);
			decodedAddress = static_cast<uint16_t>(base + regYVal);
			decodedValue = readByte(decodedAddress);
			break;
		}
		case Opcodes::AddrMode::Relative:
		{
			uint8_t offRaw = readByte(pcVal);
			pc.updateValue(std::bitset<16>(static_cast<unsigned long>(pcVal + 1)));
			uint16_t nextPc = static_cast<uint16_t>(pc.get().to_ulong());
			int8_t off = static_cast<int8_t>(offRaw);
			decodedAddress = static_cast<uint16_t>(nextPc + off);
			decodedValue = offRaw;
			break;
		}
		case Opcodes::AddrMode::IndirectX:
		{
			uint8_t base = readByte(pcVal);
			pc.updateValue(std::bitset<16>(static_cast<unsigned long>(pcVal + 1)));
			uint8_t zp = static_cast<uint8_t>(base + regXVal);
			decodedAddress = readAddrZP(zp);
			decodedValue = readByte(decodedAddress);
			break;
		}
		case Opcodes::AddrMode::IndirectY:
		{
			uint8_t zp = readByte(pcVal);
			pc.updateValue(std::bitset<16>(static_cast<unsigned long>(pcVal + 1)));
			uint16_t base = readAddrZP(zp);
			decodedAddress = static_cast<uint16_t>(base + regYVal);
			decodedValue = readByte(decodedAddress);
			break;
		}
		case Opcodes::AddrMode::Indirect:
		{
			uint8_t lo = readByte(pcVal);
			uint8_t hi = readByte(static_cast<uint16_t>(pcVal + 1));
			pc.updateValue(std::bitset<16>(static_cast<unsigned long>(pcVal + 2)));
			uint16_t ptr = static_cast<uint16_t>(lo) | (static_cast<uint16_t>(hi) << 8);
			uint16_t ptrHi = (ptr & 0xFF00) | ((ptr + 1) & 0x00FF);
			uint8_t effLo = readByte(ptr);
			uint8_t effHi = readByte(ptrHi);
			decodedAddress = static_cast<uint16_t>(effLo) | (static_cast<uint16_t>(effHi) << 8);
			decodedValue = 0;
			break;
		}
	}

	_opcode.setDecoded(decodedValue, decodedAddress, operandAddress);
	std::cout  << "decode\n";
	return State::Execute;
}

fsm::State fsm::execute(void)
{
	if (decodedHandler == nullptr)
		decodedHandler = _opcode[ir];
	_opcode.dispatchHandler(decodedHandler);
	logRegisters("execute end");
	return State::Fetch;
}

uint8_t fsm::get_ir(void) const
{
	return ir;
}

void fsm::logRegisters(const char* phase) const
{
	auto hex8 = [](const auto& reg) {
		return static_cast<unsigned long>(reg.get().to_ulong());
	};
	auto flag = [this](Reg<8>::statusFlags f) {
		return status.isFlagSet(f) ? 1 : 0;
	};
	std::cout << "[" << phase << "]"
		<< " PC=0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << hex8(pc)
		<< " ACC=0x" << std::setw(2) << hex8(acc)
		<< " X=0x" << std::setw(2) << hex8(regX)
		<< " Y=0x" << std::setw(2) << hex8(regY)
		<< " SP=0x" << std::setw(2) << hex8(sp)
		<< " STATUS[N=" << std::dec << flag(Reg<8>::statusFlags::negative)
		<< " V=" << flag(Reg<8>::statusFlags::overflow)
		<< " U=" << flag(Reg<8>::statusFlags::noEffect)
		<< " B=" << flag(Reg<8>::statusFlags::bFlag)
		<< " D=" << flag(Reg<8>::statusFlags::decimal)
		<< " I=" << flag(Reg<8>::statusFlags::interruptDisable)
		<< " Z=" << flag(Reg<8>::statusFlags::zero)
		<< " C=" << flag(Reg<8>::statusFlags::carry) << "]"
		<< " IR=0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(ir)
		<< std::dec << std::nouppercase << std::setfill(' ') << std::endl;
}

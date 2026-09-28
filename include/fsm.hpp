#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <utility>
#include "opcodes.hpp"
#include "memory.hpp"
#include "reg.hpp"


class fsm
{
	public:
		enum class State : std::size_t { Fetch = 0, Decode, Execute, Count };
	private:
		Memory& mem;
		Reg<16>& pc;
		Reg<8>& acc;
		Reg<8>& regX;
		Reg<8>& regY;
		Reg<8>& sp;
		Reg<8>& status;
		uint8_t ir;
		State state;
		std::array<std::function<State()>, static_cast<std::size_t>(State::Count) > states;
		Opcodes _opcode;
		Opcodes::Handler decodedHandler{nullptr};
		Opcodes::AddrMode decodedMode{Opcodes::AddrMode::Implied};
		uint8_t decodedValue{0};
		uint16_t decodedAddress{0};
		uint16_t operandAddress{0};
		State fetch(void);
		State decode(void);
		State execute(void);
		void logRegisters(const char* phase) const;
	public:
		fsm(Memory& mem_, Reg<16>& pc_, Reg<8>& acc_, Reg<8>& x_, Reg<8>& y_, Reg<8>& sp_, Reg<8>& status_);
		uint8_t get_ir(void) const;
		Opcodes::Handler get_decodedHandler(void) const { return decodedHandler; }
		Opcodes::AddrMode get_decodedMode(void) const { return decodedMode; }
		uint8_t get_decodedValue(void) const { return decodedValue; }
		uint16_t get_decodedAddress(void) const { return decodedAddress; }
		uint16_t get_operandAddress(void) const { return operandAddress; }
		State get_state(void) const { return state; }
		void encode(void) pre (std::to_underlying(state) < states.size());
};

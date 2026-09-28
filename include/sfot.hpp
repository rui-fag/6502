#pragma once

#include "fsm.hpp"
#include "memory.hpp"
#include "reg.hpp"

#include <atomic>
#include <bitset>
#include <cstdint>

class sfot
{
	private:
		static constexpr uint16_t kResetVector  = 0xFFFC;
		static constexpr uint16_t kResetVectorHi = 0xFFFD;
		static constexpr uint8_t  kResetSP     = 0xFD;
		static constexpr uint8_t  kResetStatus = 0b00000100;
		static constexpr uint8_t  kResetZero   = 0x00;

		Reg<16> pc_;
		Reg<8>  acc_;
		Reg<8>  regX_;
		Reg<8>  regY_;
		Reg<8>  sp_;
		Reg<8>  status_;
		Memory  mem_;
		fsm     cpu_;

		std::atomic<bool> running_{false};

	public:
		sfot();
		~sfot() = default;

		sfot(const sfot&) = delete;
		sfot& operator=(const sfot&) = delete;
		sfot(sfot&&) = delete;
		sfot& operator=(sfot&&) = delete;

		void step(void);

		void run(void);

		void stop(void);

		void reset(void);

		Memory& memory(void) { return mem_; }
		const Memory& memory(void) const { return mem_; }
		fsm& cpu(void) { return cpu_; }
		const fsm& cpu(void) const { return cpu_; }
		Reg<16>& pc(void) { return pc_; }
		Reg<8>& acc(void) { return acc_; }
		Reg<8>& regX(void) { return regX_; }
		Reg<8>& regY(void) { return regY_; }
		Reg<8>& sp(void) { return sp_; }
		Reg<8>& status(void) { return status_; }
		bool isRunning(void) const { return running_.load(); }
};

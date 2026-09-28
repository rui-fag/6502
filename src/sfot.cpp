#include "sfot.hpp"

#include <bitset>
#include <chrono>
#include <cstdint>
#include <thread>

sfot::sfot(void)
	: pc_(std::bitset<16>(0x0000)),
	  acc_(std::bitset<8>(kResetZero)),
	  regX_(std::bitset<8>(kResetZero)),
	  regY_(std::bitset<8>(kResetZero)),
	  sp_(std::bitset<8>(kResetSP)),
	  status_(std::bitset<8>(kResetStatus)),
	  mem_(),
	  cpu_(mem_, pc_, acc_, regX_, regY_, sp_, status_)
{
	reset();
}

void sfot::step(void)
{
	cpu_.encode();
}

void sfot::run(void)
{
	running_.store(true);
	while (running_.load())
	{
		step();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void sfot::stop(void)
{
	running_.store(false);
}

void sfot::reset(void)
{
	stop();
	uint8_t lo = std::to_integer<uint8_t>(mem_[kResetVector]);
	uint8_t hi = std::to_integer<uint8_t>(mem_[kResetVectorHi]);
	uint16_t vec = static_cast<uint16_t>(lo) | (static_cast<uint16_t>(hi) << 8);
	pc_.updateValue(std::bitset<16>(vec));
	acc_.updateValue(std::bitset<8>(kResetZero));
	regX_.updateValue(std::bitset<8>(kResetZero));
	regY_.updateValue(std::bitset<8>(kResetZero));
	sp_.updateValue(std::bitset<8>(kResetSP));
	status_.updateValue(std::bitset<8>(kResetStatus));
}

/*
Memory map used

Address       Size       Typical use
────────────────────────────────────────────
$0000-$00FF    256 B     Zero Page RAM
$0100-$01FF    256 B     Stack
$0200-$7FFF   ~31.5 KB   General RAM
$8000-$BFFF    16 KB     ROM / RAM / I/O
$C000-$DFFF     8 KB     ROM / I/O
$E000-$FFFF     8 KB     ROM

*/

#pragma once
#include <array>
#include <contracts>
#include <cstddef>
#include <cstdint>

class Memory
{
	private:
		std::array<std::byte, 256  > zeroPageRam;
		std::array<std::byte, 256  > stack;
		std::array<std::byte, 32256> generalRam;
		std::array<std::byte, 16384> RAM;
		std::array<std::byte, 8192 > ROM1;
		std::array<std::byte, 8192 > ROM2;

	public:
		static constexpr uint16_t zeroPageRamBase = 0x0000;
		static constexpr uint16_t stackBase = 0x0100;
		static constexpr uint16_t generalRamBase = 0x0200;
		static constexpr uint16_t ramBase = 0x8000;
		static constexpr uint16_t rom1Base = 0xC000;
		static constexpr uint16_t rom2Base = 0xE000;
		Memory();
		std::byte& operator[](uint16_t index)
			pre (index >= 0x0000 && index <= 0xFFFF);
		std::byte operator[](uint16_t index) const
			pre (index >= 0x0000 && index <= 0xFFFF);
};



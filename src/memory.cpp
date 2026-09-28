#include "memory.hpp"
#include <contracts>
#include <cstddef>
#include <cstdint>

Memory::Memory()
	:zeroPageRam{},
	stack{},
	generalRam{},
	RAM{},
	ROM1{},
	ROM2{}
{
	(*this)[0xFFFC] = static_cast<std::byte> (rom1Base & 0xFF);
	(*this)[0xFFFD] = static_cast<std::byte> ((rom1Base >> 8) & 0xFF);
}

std::byte& Memory::operator[](uint16_t index)
pre (index >= 0x0000 && index <= 0xFFFF)
{
	if(index <= 0x00FF)
		return zeroPageRam[index - zeroPageRamBase];
	else if(index <= 0x01FF)
		return stack[index - stackBase];
	else if(index <= 0x7FFF)
		return generalRam[index - generalRamBase];
	else if(index <= 0xBFFF)
		return RAM[index - ramBase];
	else if(index <= 0xDFFF)
		return ROM1[index - rom1Base];
	else
		return ROM2[index - rom2Base];
}

std::byte Memory::operator[](uint16_t index) const
pre (index >= 0x0000 && index <= 0xFFFF)
{
	if(index <= 0x00FF)
		return zeroPageRam[index - zeroPageRamBase];
	else if(index <= 0x01FF)
		return stack[index - stackBase];
	else if(index <= 0x7FFF)
		return generalRam[index - generalRamBase];
	else if(index <= 0xBFFF)
		return RAM[index - ramBase];
	else if(index <= 0xDFFF)
		return ROM1[index - rom1Base];
	else
		return ROM2[index - rom2Base];
}

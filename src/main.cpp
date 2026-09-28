#include "sfot.hpp"
#include "loader.hpp"
#include <cstdint>
#include <cstdio>

int main(void)
{
	sfot cpu;
	Loader _loader(cpu.memory());


	if (!_loader.loadMemory("a.out"))
		std::printf("load failed\n");

	cpu.reset();

	Memory& mem = cpu.memory();
	for (uint16_t i = Memory::rom1Base; i < Memory::rom1Base + 128; ++i) {
		if (i % 16 == 0)
			std::printf("%04X:", i);
		std::printf(" %02X", static_cast<uint8_t>(mem[i]));
		if (i % 16 == 15 || i == 127)
			std::printf("\n");
	}

	cpu.run();
}

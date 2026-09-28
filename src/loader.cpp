#include "loader.hpp"
#include <cstdint>
#include <fstream>

Loader::Loader(Memory& mem)
	: mem_(mem)
{}

std::expected<void, FileError> Loader::loadMemory(const char* fileName)
{
	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open()) {
		return std::unexpected(FileError::NotFound);
	}

	char byte;
	uint32_t addr = Memory::rom1Base;
	while (file.get(byte) && addr <= 0xFFFF) {
		mem_[static_cast<uint16_t>(addr++)] = static_cast<std::byte>(byte);
	}

	if (file.bad()) {
		return std::unexpected(FileError::ReadError);
	}

	return {};
}

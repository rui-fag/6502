#pragma once
#include <expected>
#include "memory.hpp"

enum class FileError
{
	NotFound,
	ReadError
};

class Loader
{
	private:
		Memory& mem_;
	public:
		explicit Loader(Memory& mem);
		std::expected<void, FileError> loadMemory(const char*);
};

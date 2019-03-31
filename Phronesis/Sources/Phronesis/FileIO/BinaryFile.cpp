
#include "BinaryFile.hpp"

#include <fstream>

using namespace Phronesis;

std::vector<char> BinaryFile::read(const std::string& filename)
{
	// std::ios::ate is for reading at the end of the file
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if(!file.is_open())
	{
		throw std::runtime_error("FileIO error: Failed to open file " + filename);
	}

	// so we can use the read position to determine the size of the file and allocate a buffer
	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	// seek back to the beginning of the file and read all of the bytes at once
	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();
	return buffer;
}

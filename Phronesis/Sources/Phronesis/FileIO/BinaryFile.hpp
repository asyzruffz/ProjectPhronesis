#pragma once

#include <vector>

namespace Phronesis
{
	class BinaryFile
	{
	public:
		static std::vector<char> read(const std::string& filename);
	};
}

#pragma once

#include <vector>

namespace Phronesis
{
	class Directory
	{
	public:
		static std::vector<std::string> getAllFilesIn(const std::string& directoryPath);
	};
}

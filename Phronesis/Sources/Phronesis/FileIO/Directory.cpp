
#include "StdAfx.hpp"
#include "Directory.hpp"

using namespace Phronesis;

std::vector<std::string> Directory::getAllFilesIn(const std::string& directoryPath)
{
	std::vector<std::string> filePaths;

	for(const auto& entry : std::filesystem::directory_iterator(directoryPath))
	{
		filePaths.push_back(entry.path().string());
	}

	return filePaths;
}

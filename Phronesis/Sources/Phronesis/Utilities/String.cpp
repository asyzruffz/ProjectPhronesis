
#include "StdAfx.hpp"
#include "String.hpp"

using namespace Phronesis;

std::string String::lowercase(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}

std::string String::uppercase(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), toupper);
	return str;
}

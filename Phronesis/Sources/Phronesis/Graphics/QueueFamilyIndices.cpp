
#include "StdAfx.h"
#include "QueueFamilyIndices.hpp"

using namespace Phronesis;


bool QueueFamilyIndices::isComplete()
{
	return graphicsFamily.has_value() && presentationFamily.has_value();
}

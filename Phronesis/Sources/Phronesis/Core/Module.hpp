#pragma once

#include "Phronesis/Utilities/TypeInfo.hpp"

namespace Phronesis
{
	class Module
	{
	public:

		enum class Stage
		{
			Always, Pre, Normal, Post, Render
		};

		virtual ~Module() = default;

		virtual void update() = 0;
	};

	template class TypeInfo<Module>;

	template<typename T>
	TypeID GetModuleTypeId() noexcept
	{
		static_assert(std::is_base_of<Module, T>::value, "T must be a Module.");
		return TypeInfo<Module>::GetTypeId<T>();
	}
}

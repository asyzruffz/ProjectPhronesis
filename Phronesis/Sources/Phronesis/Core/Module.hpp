#pragma once

#include "Phronesis/Utilities/TypeInfo.hpp"

namespace Phronesis
{
	class Module
	{
	public:

		enum class Stage
		{
			Always, Pre, Normal, Post, Physics, Render
		};

		virtual ~Module() = default;

		typedef std::unique_ptr<Module> Ptr;

		virtual void update() = 0;
		virtual void dispose() = 0;

		template<typename T>
		static bool hasModule();

		template<typename T>
		static T* getModule();
	};

	template class TypeInfo<Module>;

	template<typename T>
	TypeID getModuleTypeId() noexcept
	{
		static_assert(std::is_base_of<Module, T>::value, "[ERROR] T must be a Module");
		return TypeInfo<Module>::getTypeId<T>();
	}
}

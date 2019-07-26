#pragma once

#include <cstdlib>

namespace Phronesis
{
	using TypeID = std::size_t;

	template<typename T>
	class TypeInfo
	{
	public:
		TypeInfo() = delete;

		template<typename K>
		inline static TypeID getTypeId()
		{
			static const auto id = getNextTypeId();
			return id;
		}

	private:
		inline static TypeID getNextTypeId() noexcept
		{
			const auto id = nextTypeId;
			++nextTypeId;
			return id;
		}

		// next type ID for T.
		static TypeID nextTypeId;
	};

	template<typename K> TypeID TypeInfo<K>::nextTypeId = 0;
}

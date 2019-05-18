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
		inline static TypeID GetTypeId()
		{
			static const auto id = NextTypeId();
			return id;
		}

	private:
		inline static TypeID NextTypeId() noexcept
		{
			const auto id = m_nextTypeId;
			++m_nextTypeId;
			return id;
		}

		// next type ID for T.
		static TypeID m_nextTypeId;
	};

	template<typename K> TypeID TypeInfo<K>::m_nextTypeId = 0;
}

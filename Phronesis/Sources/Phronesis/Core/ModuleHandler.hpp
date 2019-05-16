#pragma once

#include <stdexcept>
#include <memory>
#include <unordered_map>

#include "Module.hpp"

namespace Phronesis
{
	struct StagedModule
	{
		std::unique_ptr<Module> module;
		Module::Stage stage;
	};

	class ModuleHandler
	{
	public:
		ModuleHandler();
		~ModuleHandler();

		template<typename T>
		bool has() const
		{
			const auto it = modules.find(GetModuleTypeId<T>());
			return it != modules.end() && it->second.module != nullptr;
		}

		template<typename T>
		T* get() const
		{
			const auto it = modules.find(GetModuleTypeId<T>());

			if(it == modules.end() || it->second.module == nullptr)
			{
				throw std::runtime_error("Module Handler does not have requested Module");
				return nullptr;
			}

			return static_cast<T*>(it->second.module.get());
		}

		template<typename T>
		void add(const Module::Stage& stage)
		{
			const auto typeId = GetModuleTypeId<T>();
			modules[typeId] = { std::unique_ptr<Module>(static_cast<Module*>(new T)), stage };
		}

		template<typename T>
		void remove()
		{
			modules.erase(GetModuleTypeId<T>());
		}

	private:
		friend class Game;

		void updateStage(const Module::Stage& stage);

	private:
		std::unordered_map<TypeID, StagedModule> modules;
	};
}

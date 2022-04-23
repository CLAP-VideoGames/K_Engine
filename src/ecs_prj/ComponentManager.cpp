#include "ComponentManager.h"

#include <ecs_prj/Component.h>

#include <log_prj/LogManager.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
	std::unique_ptr<ComponentManager> ComponentManager::instance = nullptr;

	ComponentManager::ComponentManager() = default;

	ComponentManager::~ComponentManager() = default;

	ComponentManager* ComponentManager::GetInstance() {
		return instance.get();
	}

	bool ComponentManager::Init() {
		try {
			instance.reset(new ComponentManager());
		}
		catch (const std::exception& e) {
			return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, e.what());
		}

		return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "Component manager initialization success");
	}

	bool ComponentManager::Shutdown() {
		try {
			instance.get()->availableComponents.clear();

			instance.reset(nullptr);
		}
		catch (const std::exception& e) {
			return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, e.what());
		}

		return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "Component manager shutdown success");
	}

	Component* ComponentManager::createByName(std::string name) {
		//We check if the component exists
		if (!existingComponent(name)) {
			throw std::invalid_argument("There is no component with that name");
		}
		auto iterator = availableComponents.find(name);
		Component* newComponent = (iterator->second)();

		return newComponent;
	}

	std::vector<std::string> ComponentManager::getAvailableComponents()
	{
		std::vector<std::string> avComp;
		for (auto it = availableComponents.begin(); it != availableComponents.end(); ++it)
			avComp.push_back(it->first);

		return avComp;
	}

	bool ComponentManager::existingComponent(std::string compName) {
		auto c = availableComponents.find(compName);

		//If it is not the end, the component exists
		return !(c == availableComponents.end());
	}
}
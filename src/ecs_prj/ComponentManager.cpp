#include "ComponentManager.h"

namespace K_Engine {
	std::unique_ptr<ComponentManager> ComponentManager::instance = nullptr;

	ComponentManager::ComponentManager() = default;

	ComponentManager::~ComponentManager() = default;

	ComponentManager* ComponentManager::GetInstance()
	{
		return instance.get();
	}

	bool ComponentManager::Init(std::string n)
	{
		instance.reset(new ComponentManager());

		instance.get()->name = n;

		return true;
	}

	std::vector<std::string> ComponentManager::getAvailableComponents(){
		return std::vector<std::string>(availableComponents.begin(), availableComponents.end());
	}

	bool ComponentManager::existingComponent(std::string compName)
	{
		auto c = availableComponents.find(compName);

		//If it is not the end, the component exists
		return !(c == availableComponents.end());
	}
}
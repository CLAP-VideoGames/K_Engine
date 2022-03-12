#include "ComponentManager.h"

#include "Transform.h"
#include "MeshRenderer.h"

std::unique_ptr<ComponentManager> ComponentManager::instance = nullptr;

ComponentManager::ComponentManager() = default;

ComponentManager* ComponentManager::GetInstance()
{
	return instance.get();
}

bool ComponentManager::Init(std::string n)
{
	try {
		instance.reset(new ComponentManager());

		instance.get()->name = n;

		instance.get()->availableComponents.emplace(Transform::GetId(), new Transform());
		instance.get()->availableComponents.emplace(MeshRenderer::GetId(), new MeshRenderer());
	}
	catch (const std::exception&) {
		return false;
	}

	return true;
}

Component* ComponentManager::create(std::string compName)
{
	//We check if the component exists
	auto c = availableComponents.find(compName);

	if (c == availableComponents.end()) {
		throw std::invalid_argument("There is no component with that name");
	}

	//We return a new instance of our component
	return availableComponents[compName];
}

bool ComponentManager::existingComponent(std::string compName)
{
	auto c = availableComponents.find(compName);

	//If it is not the end, the component exists
	return !(c == availableComponents.end());
}

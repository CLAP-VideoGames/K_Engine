#include "ComponentManager.h"

#include "Transform.h"
#include "MeshRenderer.h"

#include <stdexcept>

std::unique_ptr<ComponentManager> ComponentManager::instance = nullptr;

ComponentManager::ComponentManager() = default;

ComponentManager* ComponentManager::GetInstance()
{
	return instance.get();
}

bool ComponentManager::Init()
{
	//Base components for our engine(Use this comand with every base component)
	//instance.get()->availableComponents.emplace(Transform::GetId(), tr);
	//instance.get()->availableComponents.emplace(MeshRenderer::GetId(), new MeshRenderer());

	return true;
}


template<typename T, typename ...Ts>
T* ComponentManager::create(Ts && ...args)
{
	//We check if the component exists
	auto c = availableComponents.find(T::GetId());

	if (c == availableComponents.end()) {
		throw std::invalid_argument("There is no component with that name");
	}

	//We return a new instance of our component
	auto newComponent = new T();

	return newComponent;
}

template<typename T>
void ComponentManager::add()
{
	std::string compName;

	//The user is not allowed to add a component without an static GetId() method
	try {
		compName = T::GetId();

	}
	catch (std::string msg) {
		throw std::invalid_argument("Your component does not contain a GetId() method, declare it and try again");
	}

	//If the component is not alredy in the component map, we add it
	auto c = availableComponents.find(compName);

	if (c == availableComponents.end()) {
		availableComponents.emplace(T::GetId(), new T());
	}
}

bool ComponentManager::existingComponent(std::string compName)
{
	auto c = availableComponents.find(compName);

	//If it is not the end, the component exists
	return !(c == availableComponents.end());
}

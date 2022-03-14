#include "ComponentManager.h"

#include <ecs_prj/Transform.h>
#include <ecs_prj/MeshRenderer.h>

std::unique_ptr<ComponentManager> ComponentManager::instance = nullptr;

ComponentManager::ComponentManager() = default;

ComponentManager::~ComponentManager() = default;

ComponentManager* ComponentManager::GetInstance()
{
	return instance.get();
}

bool ComponentManager::Init(std::string n)
{
	try {
		instance.reset(new ComponentManager());

		instance.get()->name = n;

		instance.get()->availableComponents.emplace(Transform::GetId(), new Transform(nullptr));
		instance.get()->availableComponents.emplace(MeshRenderer::GetId(), new MeshRenderer(nullptr));
	}
	catch (const std::exception&) {
		return false;
	}

	return true;
}

bool ComponentManager::existingComponent(std::string compName)
{
	auto c = availableComponents.find(compName);

	//If it is not the end, the component exists
	return !(c == availableComponents.end());
}

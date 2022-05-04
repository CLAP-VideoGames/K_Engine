#include "Component.h"

#include <stdexcept>

#include <utils_prj/K_Map.h>

namespace K_Engine {

	Component::Component() {
		enable = true;
		toDestroy = false;
		entity = nullptr;
	}

	Component::Component(Entity* ent) {
		enable = true;
		entity = ent;
	}

	Component::~Component() = default;

	void Component::awake() {};

	void Component::start() {}

	void Component::onEnable() {};
	
	void Component::update(int frameTime) {};
	
	void Component::physicsUpdate(int deltaTime) {}

	void Component::onDisable() {};

	void Component::debug() {}

	void Component::setActive(bool a)
	{
		enable = a;

		if (enable)onEnable();
		else onDisable();
	}
	void Component::destroy()
	{
		toDestroy = true;
	}
}
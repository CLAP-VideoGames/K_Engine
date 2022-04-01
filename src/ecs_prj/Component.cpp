#include "Component.h"

#include <stdexcept>

namespace K_Engine {
	Component::Component(std::string id_ = "unknown", Entity* ent = nullptr)
	{
		enable = true;
		entity = ent;

		id = id_;
		if (id == "unknown")
			throw std::invalid_argument("You must define the id of your component");

	}

	Component::~Component() = default;

	void Component::awake() {};

	void Component::start() {};

	void Component::onEnable() {};
	
	void Component::update(int frameTime) {};
	
	void Component::physicsUpdate(int deltaTime) {}

	void Component::onDisable() {};

	void Component::debug() {}

	void Component::setActive(bool a)
	{
		enable = a;

		if (enable) {
			onEnable();
			awake();
		}
		else onDisable();
	}
}
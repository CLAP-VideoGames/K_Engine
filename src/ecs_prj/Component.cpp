#include "Component.h"
#include <stdexcept>

Component::Component(std::string id_)
{
	id = id_;

	if (id == "unknown") {
		throw std::invalid_argument("You must define the id of your component");
	}

	enable = true;
}

Component::~Component()
{

}

void Component::setActive(bool a)
{
	enable = a;

	if (enable) onEnable();
	else onDisable();
}

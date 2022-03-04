#include "Component.h"
#include <stdexcept>

Component::Component(string id_)
{
	id = id_;

	if (id == "unknown") {
		throw std::invalid_argument("You must define the id of your component");
	}

	active = true;
}

Component::~Component()
{

}

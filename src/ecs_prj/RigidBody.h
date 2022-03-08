#pragma once
#include "Component.h"
#include <vector>

class RigidBody : public Component
{
public:
	RigidBody();
	~RigidBody();

	//Required method for the component name
	static std::string getId() { return name; }

protected:


private:

	//Required
	static std::string name;

	//
	bool rotationConstraints[3]{ false, false, false };
	//
	bool traslationConstraints[3]{ false, false, false };
};
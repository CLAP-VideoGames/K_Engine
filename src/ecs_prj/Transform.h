#pragma once
#include "Component.h"
#include <vector>

class Transform : public Component
{
public:
	Transform();
	~Transform();

	static std::string getId() { return "Transform"; }

protected:

	
private:

	double position[3];
	double scale[3];
	double rotation[3];

};
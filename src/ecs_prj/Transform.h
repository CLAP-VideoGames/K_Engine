#pragma once
#include "Component.h"
#include <vector>

class Transform : public Component
{
public:
	Transform();
	~Transform();

	//Required method for the component name
	static std::string getId() { return name; }

protected:

	
private:

	//Required
	static std::string name;

	//Position, scale and rotation with their default initialization

	//array with the x y z coordinates of the position
	double position[3]{0,0,0};
	//array with the x y z coordinates of the scale
	double scale[3]{1,1,1};
	//array with the x y z coordinates of the rotation
	double rotation[3]{0,0,0};

};
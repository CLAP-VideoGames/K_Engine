#include "Transform.h"
//Required
std::string Transform::name = "Transform";

Transform::Transform() : Component("Transform")
{
	name = id;
}

Transform::~Transform()
{

}

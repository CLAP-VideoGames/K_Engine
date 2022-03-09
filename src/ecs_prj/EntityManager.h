#pragma once
#include <vector>

class Entity;
/*
* This class is in charge of having track of our entitys and updating them
* also erasing them when necesary
*/
class EntityManager
{
public:
	EntityManager();
	~EntityManager() {};

	//Methos to add and Entity that return it to the user
	Entity* addEntity();

	//where every entity is updated
	void update();

private:

	//Our entity vector
	std::vector<Entity*>entities;
};
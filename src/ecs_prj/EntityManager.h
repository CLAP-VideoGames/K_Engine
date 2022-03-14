#pragma once
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

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

	//The destructor erases and deletes every entity in existence
	~EntityManager();

	//Method to add and Entity that return it to the user
	Entity* addEntity();

	//where every entity is updated
	void update();

private:
	//Our entity vector
	std::vector<Entity*> entities;
};
#endif // ENTITYMANAGER_H
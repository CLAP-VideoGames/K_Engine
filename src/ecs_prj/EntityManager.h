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

	//where the physics
	void fixedUpdate();

	//where every component calls it start method
	//WE MUST CALL THIS AFTER THE INIT OF THIS SINGLETON AND AFTER THE READ OF THE MAP
	//JOSEDA LEE AQUI SI NO FUNICONA 
	//DESPUES DEL INTI DE ESTE SINGLETON Y DESPUES DE LA LECTURA DEL MAPA
	//(sorry caps)
	void start();

private:
	//Our entity vector
	std::vector<Entity*> entities;
};

#endif // ENTITYMANAGER_H
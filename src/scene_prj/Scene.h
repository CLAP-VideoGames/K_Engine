#pragma once
#ifndef SCENE_H
#define SCENE_H
#include <string>
class EntityManager;

class Scene
{
public:
	//Creates the entityManager of our scene
	Scene();

	//Deletes the entityManager of our scene
	~Scene();
	
	//Init is called once when the Scene is push on top of the scenes stack
	virtual void init() {};

	//Update is called once per frame
	virtual void update() {};

private:

	//In charge of keeping track of the entities of the scene
	EntityManager* entMan;
};

#endif
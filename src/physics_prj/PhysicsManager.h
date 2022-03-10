#pragma once
#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <memory>

template<typename T>
class btAlignedObjectArray;

class btCollisionShape;
class btDiscreteDynamicsWorld;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class CustomVector3;
class btVector3;

namespace BtOgre {
	class DynamicsWorld;
}

class PhysicsManager{

public:
	PhysicsManager();
	~PhysicsManager();

	static PhysicsManager* GetInstance();

	static bool Init(const CustomVector3& gravity);
	static bool Shutdown();

	void update(float const& delta);
	void exampleObjects();

private:
	static std::unique_ptr<PhysicsManager> instance;

	btVector3* gravity;
	btCollisionDispatcher* dispatcher; 
	btBroadphaseInterface* overlappingPairCache;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btSequentialImpulseConstraintSolver* solver;
	btAlignedObjectArray<btCollisionShape*>* collisionShapes;

	BtOgre::DynamicsWorld* dynamicWorld;

	int numIterations_;

	bool initWorld(const CustomVector3& gravity);
	bool releaseWorld();
};
#endif // PHYSICSMANAGER_H
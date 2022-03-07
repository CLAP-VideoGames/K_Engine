#pragma once
/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2007 Erwin Coumans  https://bulletphysics.org
This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:
1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

///-----includes_start-----
#include <btBulletDynamicsCommon.h>
#include <memory>

class PhysicsManager{

public:
	static PhysicsManager* getInstance();

	void init(int numIterations, int step, const btVector3& gravity = btVector3(0, -9.8f, 0));

	~PhysicsManager();

	void Update();

private:
	static std::unique_ptr<PhysicsManager> instance;

	btDiscreteDynamicsWorld* dynamicsWorld;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
	btCollisionDispatcher* dispatcher; 
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btVector3 gravity;

	int numIterations_;
	void exampleObjects();
};


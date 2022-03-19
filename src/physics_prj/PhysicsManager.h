#pragma once
#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#define BIT(x) (1<<(x))
#include <memory>

template<typename T>
class btAlignedObjectArray;

class btCollisionShape;
class btDiscreteDynamicsWorld;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btOverlapFilterCallback;
class btVector3;
class btTransform;
class DynamicsWorld;
class btRigidBody;
struct CustomVector3;
class btDynamicsWorld;


enum class ColliderType {
	CT_BOX,
	CT_SPHERE,
	CT_TRIMESH,
	CT_HULL
};

enum class BodyType {
	BT_STATIC,
	BT_DYNAMIC,
};

class PhysicsManager{
public:
	struct ColissionCallBack;

	enum CollisionLayer {
		COL_NOTHING = 0,
		COL_PLAYER = BIT(1),
		COL_WORLD = BIT(2),
	};

	int playerCollidesWith = CollisionLayer::COL_PLAYER | CollisionLayer::COL_WORLD;

	PhysicsManager();
	~PhysicsManager();

	static PhysicsManager* GetInstance();

	static bool Init(int numIterations, int step, const CustomVector3& gravity);
	static bool Shutdown();

	void update();
	void exampleObjects();
	void changeCollisionFiltering(btRigidBody* rb, int group, int mask);
	btTransform* createTransform(CustomVector3 const& position, CustomVector3 const& rotation);
	void changeGravity(CustomVector3 const& grav);

	DynamicsWorld* getWorld() const;

private:
	static std::unique_ptr<PhysicsManager> instance;

	btVector3* gravity;
	btDynamicsWorld* btWorld;
	DynamicsWorld* dynamicsWorld_;

	int numIterations_;

	bool initWorld(int numIterations, int step, const btVector3& gravity);
	bool releaseWorld();
};
#endif // PHYSICSMANAGER_H
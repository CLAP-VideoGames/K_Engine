#pragma once
#ifndef _DYNAMICSWORLD_H_
#define _DYNAMICSWORLD_H_

#include <memory>
class btDynamicsWorld;
class btVector3;
class btRigidBody;
class btManifoldPoint;
class btCollisionConfiguration;
class btCollisionDispatcher;
class btConstraintSolver;
class btBroadphaseInterface;
class btBoxShape;
class btSphereShape;
class btTransform;
class btCollisionShape;
class CollisionListener;
enum class ColliderType;

template<typename T>
class btAlignedObjectArray;

class DynamicsWorld
{
private:
	std::unique_ptr<btCollisionConfiguration> mCollisionConfig;
	std::unique_ptr<btCollisionDispatcher> mDispatcher;
	std::unique_ptr<btConstraintSolver> mSolver;
	std::unique_ptr<btBroadphaseInterface> mBroadphase;
	btAlignedObjectArray<btCollisionShape*>* collisionShapes;

	btDynamicsWorld* btWorld_;
public:

	struct ColissionCallBack;

	explicit DynamicsWorld(btVector3 const& gravity);
	DynamicsWorld(btDynamicsWorld* btWorld) : btWorld_(btWorld) {}

	~DynamicsWorld();

	btDynamicsWorld* getBtWorld() const { return btWorld_; };

	btRigidBody* addRigidBody(ColliderType ct, const btTransform& transform, btVector3 const& size, float mass, int group, int mask, CollisionListener* colList = nullptr);

	btBoxShape* createBoxCollider(btVector3 const& size);

	btSphereShape* createSphereCollider(btVector3 const& radius);
};

#endif _DYNAMICSWORLD_H_

#pragma once
#ifndef _DYNAMICSWORLD_H_
#define _DYNAMICSWORLD_H_

#include <memory>

template<typename T>
class btAlignedObjectArray;

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

enum class ColliderType;
enum class BodyType;

namespace K_Engine {
	class CollisionListener;

	class DynamicsWorld {
	private:
		std::unique_ptr<btCollisionConfiguration> mCollisionConfig;
		std::unique_ptr<btCollisionDispatcher> mDispatcher;
		std::unique_ptr<btConstraintSolver> mSolver;
		std::unique_ptr<btBroadphaseInterface> mBroadphase;
		btAlignedObjectArray<btCollisionShape*>* collisionShapes;

		btDynamicsWorld* btWorld_;

	public:
		struct CollisionCallBack;

		explicit DynamicsWorld(btVector3 const& gravity);
		DynamicsWorld(btDynamicsWorld* btWorld) : btWorld_(btWorld) {}

		~DynamicsWorld();

		btDynamicsWorld* getBtWorld() const { return btWorld_; };

		void scaleCollisionShape(btRigidBody* rb, btVector3 const& scale);

		btRigidBody* addRigidBody(ColliderType ct, const btTransform& transform, btVector3 const& dimensions, btVector3 const& scale, BodyType bodyType, float mass, float restitution, float friction, int group, int mask, CollisionListener* colList = nullptr);

		btBoxShape* createBoxCollider(btVector3 const& size, btVector3 const& dimensions);

		btSphereShape* createSphereCollider(btVector3 const& radius, btVector3 const& dimensions);
	};
}
#endif _DYNAMICSWORLD_H_

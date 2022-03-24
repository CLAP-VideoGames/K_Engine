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

		/// <summary>
		/// 
		/// </summary>
		/// <returns>reference to the physics world</returns>
		btDynamicsWorld* getBtWorld() const { return btWorld_; };

		/// <summary>
		/// scale the collider detection by a new given size
		/// </summary>
		/// <param name="rb">reference to the rigidbody to size</param>
		/// <param name="scale">new size</param>
		void scaleCollisionShape(btRigidBody* rb, btVector3 const& scale);

		/// <summary>
		/// Generates a generic rigidbody, given its configurations attributes 
		/// </summary>
		/// <param name="ct">Shape type of the collider</param>
		/// <param name="transform">Reference to the transform</param>
		/// <param name="dimensions">Dimensions of the body</param>
		/// <param name="scale">Scale, it should be 1,1,1 by default</param>
		/// <param name="bodyType">whether is dynamic, static...</param>
		/// <param name="mass">Mass of the body</param>
		/// <param name="restitution">Bounciness factor</param>
		/// <param name="friction">Friction factor</param>
		/// <param name="group">Group Layer, define with which layers colliders</param>
		/// <param name="mask">Which mask belongs the body</param>
		/// <param name="colList">Collision Listener</param>
		/// <returns>reference to the rigidbody</returns>
		btRigidBody* addRigidBody(ColliderType ct, const btTransform& transform, btVector3 const& dimensions, btVector3 const& scale, BodyType bodyType, float mass, float restitution, float friction, int group, int mask, CollisionListener* colList = nullptr);

		/// <summary>
		/// Creates a box collider given its size in each axis and dimensions
		/// </summary>
		/// <param name="radius">size axis</param>
		/// <param name="dimensions">dimensions, also known as scale</param>
		/// <returns>reference to a box type</returns>
		btBoxShape* createBoxCollider(btVector3 const& size, btVector3 const& dimensions);

		/// <summary>
		/// Creates a sphere collider given its radius and dimensions
		/// </summary>
		/// <param name="radius">radius </param>
		/// <param name="dimensions">dimensions, also known as scale</param>
		/// <returns>reference to a sphere type</returns>
		btSphereShape* createSphereCollider(btVector3 const& radius, btVector3 const& dimensions);
	};
}
#endif _DYNAMICSWORLD_H_

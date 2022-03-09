#pragma once
#ifndef CUSTOMBTOGRE_H
#define CUSTOMBTOGRE_H

#include <Ogre.h>
#include <btBulletDynamicsCommon.h>

namespace BtOgre {
	/// <summary>
	/// Converts variables from Ogre to Bullet and vice versa
	/// </summary>
	struct Converter {
		static Ogre::Quaternion toOgre(const btQuaternion& q) {
			return Ogre::Quaternion(q.w(), q.x(), q.y(), q.z());
		}

		static Ogre::Vector3 toOgre(const btVector3& v)
		{
			return Ogre::Vector3(v.x(), v.y(), v.z());
		}

		static btQuaternion toBullet(const Ogre::Quaternion& q)
		{
			return btQuaternion(q.x, q.y, q.z, q.w);
		}
		static btVector3 toBullet(const Ogre::Vector3& v)
		{
			return btVector3(v.x, v.y, v.z);
		}
	};

	/// <summary>
	/// All the supported colliders
	/// </summary>
	enum ColliderType { BOX, SPHERE };

	/// <summary>
	/// Creates a box collider using data from Ogre
	/// </summary>
	/// <param name="mo"> Ogre object from which to create the collider </param>
	/// <returns></returns>
	btBoxShape* createBoxCollider(const Ogre::MovableObject* mo);

	/// <summary>
	/// Creates a sphere collider using data from Ogre
	/// </summary>
	/// <param name="mo"> Ogre object from which to create the collider </param>
	/// <returns></returns>
	btSphereShape* createSphereCollider(const Ogre::MovableObject* mo);

	/// <summary>
	/// Redefines default Bullet Motion State. This version updates the Ogre node to match it's physics counterpart.
	/// In the future it will also update the component Transform
	/// </summary>
	class RigidBodyState : public btMotionState
	{
		Ogre::Node* mNode;
		// Add Transform component
	public:
		RigidBodyState(Ogre::Node* node) : mNode(node) {}

		void getWorldTransform(btTransform& ret) const override
		{
			// Maybe this can be changed to get the position and orientation from Transform instead
			ret = btTransform(Converter::toBullet(mNode->getOrientation()),
				Converter::toBullet(mNode->getPosition()));
		}

		/// <summary>
		/// Updates the position of the Ogre node and the Transform component
		/// </summary>
		/// <param name="in"> Position in Bullet </param>
		void setWorldTransform(const btTransform& in) override
		{
			btQuaternion rot = in.getRotation();
			btVector3 pos = in.getOrigin();
			mNode->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
			mNode->setPosition(pos.x(), pos.y(), pos.z());
			// Add Transform component updating
		}
	};

	/// <summary>
	/// Collision callbacks
	/// </summary>
	class CollisionListener
	{
	public:
		CollisionListener(void(*d)(void*, void* other, const btManifoldPoint& mnf), void* o) : p(d), obj(o) {};
		~CollisionListener() {};
		void(*p)(void*, void* other, const btManifoldPoint& mnf);
		void* obj;
	};

}



#endif // CUSTOMBTOGRE_H
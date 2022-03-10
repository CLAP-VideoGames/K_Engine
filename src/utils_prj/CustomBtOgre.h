#ifndef CUSTOMBTOGRE_H
#define CUSTOMBTOGRE_H

#include <btBulletDynamicsCommon.h>
#include "CustomVector.h"
#include <Ogre.h>

//namespace Ogre {
//	class Quaternion;
//	class Vector3;
//	class MovableObject;
//	class Node;
//	class Entity;
//	class Matrix4;
//	class Real;
//	class VertexData;
//	class Mesh;
//	class Renderable;
//	class IndexData;
//	class ManualObject;
//	class MeshPtr;
//	class LogManager;
//}
//
//class CustomVector3;

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

		static Ogre::Vector3 toOgre(const CustomVector3& v) {
			return Ogre::Vector3(v.x, v.y, v.z);
		}

		static CustomVector3 toCustom(const btVector3& v) {
			return CustomVector3(v.x(), v.y(), v.z());
		}

		static CustomVector3 toCustom(const Ogre::Vector3& v) {
			return CustomVector3(v.x, v.y, v.z);
		}

		static btQuaternion toBullet(const Ogre::Quaternion& q)
		{
			return btQuaternion(q.x, q.y, q.z, q.w);
		}
		static btVector3 toBullet(const Ogre::Vector3& v)
		{
			return btVector3(v.x, v.y, v.z);
		}

		static btVector3 toBullet(const CustomVector3& v) {
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

	//EXPERIMENTAL
	btBoxShape* createBoxCollider(const Ogre::Vector3 initialVector, const Ogre::Vector3 endVector);
	btBoxShape* createBoxCollider(const CustomVector3 initialVector, const CustomVector3 endVector);

	/// <summary>
	/// Creates a sphere collider using data from Ogre
	/// </summary>
	/// <param name="mo"> Ogre object from which to create the collider </param>
	/// <returns></returns>
	btSphereShape* createSphereCollider(const Ogre::MovableObject* mo);

	//EXPERIMENTAL
	btSphereShape* createSphereCollider(const float radius);

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
		/// <summary>
		/// Callback definition
		/// </summary>
		/// <param name="d"> btNearCallback used in bullet to determine collisions </param>
		/// <param name="o"> Function to callback to </param>
		CollisionListener(void(*d)(void*, void* other, const btManifoldPoint& mnf), void* o) : p(d), obj(o) {};
		~CollisionListener() {};
		void(*p)(void*, void* other, const btManifoldPoint& mnf);
		void* obj;
	};

	/// <summary>
	/// Contains all elements relevant to a physics object
	/// </summary>
	class RigidBody
	{
		btRigidBody* mBtBody;
		btDynamicsWorld* mBtWorld;
	public:
		RigidBody(btRigidBody* btBody, btDynamicsWorld* btWorld) : mBtBody(btBody), mBtWorld(btWorld) {}
		~RigidBody()
		{
			mBtWorld->removeRigidBody(mBtBody);
			delete mBtBody->getUserPointer();
			delete mBtBody->getMotionState();
			delete mBtBody->getCollisionShape();
			delete mBtBody;
		}

		btRigidBody* getBtBody() const { return mBtBody; }
	};

	/// <summary>
	/// Contains all elements necessary for a Bullet physic world
	/// </summary>
	class DynamicsWorld
	{
		std::unique_ptr<btCollisionConfiguration> mCollisionConfig;
		std::unique_ptr<btCollisionDispatcher> mDispatcher;
		std::unique_ptr<btConstraintSolver> mSolver;
		std::unique_ptr<btBroadphaseInterface> mBroadphase;
		btDynamicsWorld* mBtWorld;
	public:
		explicit DynamicsWorld(const CustomVector3& gravity);
		~DynamicsWorld();
		DynamicsWorld(btDynamicsWorld* btWorld) : mBtWorld(btWorld) {}

		btRigidBody* addRigidBody(float mass, const Ogre::Entity* ent, ColliderType ct, void(*p)(void*, void* other, const btManifoldPoint& mnf), void* listener = 0);

		btRigidBody* addRigidBody(float mass, const Ogre::SceneNode* mNode, const CustomVector3& initialPosition, const CustomVector3& endPosition,
			ColliderType ct, void(*p)(void*, void* other, const btManifoldPoint& mnf), void* listener = 0);

		btDynamicsWorld* getBtWorld() const { return mBtWorld; }
	};

	typedef std::vector<Ogre::Vector3> Vector3Array;
	typedef std::map<unsigned char, Vector3Array*> BoneIndex;

	/// <summary>
	/// Converts an Ogre mesh to a physic object
	/// </summary>
	class VertexIndexToShape
	{
	public:
		VertexIndexToShape(const Ogre::Matrix4& transform = Ogre::Matrix4::IDENTITY);
		~VertexIndexToShape();

		Ogre::Real getRadius();
		Ogre::Vector3 getSize();


		btSphereShape* createSphere();
		btBoxShape* createBox();

		const Ogre::Vector3* getVertices();
		unsigned int getVertexCount();
		const unsigned int* getIndices();
		unsigned int getIndexCount();

	protected:

		void addStaticVertexData(const Ogre::VertexData* vertex_data);

		void addAnimatedVertexData(const Ogre::VertexData* vertex_data,
			const Ogre::VertexData* blended_data,
			const Ogre::Mesh::IndexMap* indexMap);

		void addIndexData(Ogre::IndexData* data, const unsigned int offset = 0);


	protected:
		Ogre::Vector3* mVertexBuffer;
		unsigned int* mIndexBuffer;
		unsigned int        mVertexCount;
		unsigned int        mIndexCount;

		Ogre::Vector3		mBounds;
		Ogre::Real		    mBoundRadius;

		BoneIndex* mBoneIndex;

		Ogre::Matrix4		mTransform;

		Ogre::Vector3		mScale;
	};

	/// <summary>
	/// Static object converter
	/// </summary>
	class StaticMeshToShapeConverter : public VertexIndexToShape
	{
	public:

		StaticMeshToShapeConverter(Ogre::Renderable* rend, const Ogre::Matrix4& transform = Ogre::Matrix4::IDENTITY);
		StaticMeshToShapeConverter(const Ogre::Entity* entity, const Ogre::Matrix4& transform = Ogre::Matrix4::IDENTITY);
		StaticMeshToShapeConverter();

		~StaticMeshToShapeConverter() {};

		void addEntity(const Ogre::Entity* entity, const Ogre::Matrix4& transform = Ogre::Matrix4::IDENTITY);

		void addMesh(const Ogre::MeshPtr& mesh, const Ogre::Matrix4& transform = Ogre::Matrix4::IDENTITY);


	protected:

		const Ogre::Entity* mEntity;
		Ogre::SceneNode* mNode;
	};


	/// <summary>
	/// Converts a mesh or Ogre entity to a physic object. Compatible with ogre animations
	/// </summary>
	class AnimatedMeshToShapeConverter : public VertexIndexToShape
	{
	public:

		AnimatedMeshToShapeConverter(Ogre::Entity* entity, const Ogre::Matrix4& transform = Ogre::Matrix4::IDENTITY);
		AnimatedMeshToShapeConverter();
		~AnimatedMeshToShapeConverter();

		void addEntity(Ogre::Entity* entity, const Ogre::Matrix4& transform = Ogre::Matrix4::IDENTITY);
		void addMesh(const Ogre::MeshPtr& mesh, const Ogre::Matrix4& transform);

		btBoxShape* createAlignedBox(unsigned char bone,
			const Ogre::Vector3& bonePosition,
			const Ogre::Quaternion& boneOrientation);

		btBoxShape* createOrientedBox(unsigned char bone,
			const Ogre::Vector3& bonePosition,
			const Ogre::Quaternion& boneOrientation);

	protected:

		bool getBoneVertices(unsigned char bone,
			unsigned int& vertex_count,
			Ogre::Vector3*& vertices,
			const Ogre::Vector3& bonePosition);

		bool getOrientedBox(unsigned char bone,
			const Ogre::Vector3& bonePosition,
			const Ogre::Quaternion& boneOrientation,
			Ogre::Vector3& extents,
			Ogre::Vector3* axis,
			Ogre::Vector3& center);


		Ogre::Entity* mEntity;
		Ogre::SceneNode* mNode;

		Ogre::Vector3* mTransformedVerticesTemp;
		size_t               mTransformedVerticesTempSize;
	};

	/// <summary>
	/// Redefines btIDebugDraw to render colliders in Ogre
	/// </summary>
	class DebugDrawer : public btIDebugDraw
	{
		Ogre::SceneNode* mNode;
		btDynamicsWorld* mWorld;

		Ogre::ManualObject mLines;
		int mDebugMode;
	public:
		DebugDrawer(Ogre::SceneNode* node, btDynamicsWorld* world)
			: mNode(node), mWorld(world), mLines(""), mDebugMode(DBG_DrawWireframe)
		{
			mNode->attachObject(&mLines);
			mWorld->setDebugDrawer(this);
		}

		void update()
		{
			mWorld->debugDrawWorld();
			mLines.end();
		}

		void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

		void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
		{
			drawLine(PointOnB, PointOnB + normalOnB * distance * 20, color);
		}

		void reportErrorWarning(const char* warningString)
		{
			Ogre::LogManager::getSingleton().logWarning(warningString);
		}

		void draw3dText(const btVector3& location, const char* textString)
		{
		}

		void setDebugMode(int mode)
		{
			mDebugMode = mode;

			if (mDebugMode == DBG_NoDebug)
				clear();
		}

		void clear() { mLines.clear(); }

		int getDebugMode() const { return mDebugMode; }
	};
}



#endif // CUSTOMBTOGRE_H
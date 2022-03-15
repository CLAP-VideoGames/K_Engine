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


template<typename T>
class btAlignedObjectArray;

namespace Ogre {
	class Entity;
}

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
	enum ColliderType
	{
		CT_BOX,
		CT_SPHERE,
		CT_TRIMESH,
		CT_HULL
	};

	explicit DynamicsWorld(btVector3 const& gravity);
	DynamicsWorld(btDynamicsWorld* btWorld) : btWorld_(btWorld) {}

	~DynamicsWorld();

	btDynamicsWorld* getBtWorld() const { return btWorld_; };

	btRigidBody* addRigidBody(ColliderType ct, const btTransform& transform, btVector3 const& size, float mass, int group, int mask, CollisionListener* colList);

	btBoxShape* createBoxCollider(btVector3 const& size);

	btSphereShape* createSphereCollider(btVector3 const& radius);
};

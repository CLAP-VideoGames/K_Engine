#include "DynamicsWorld.h"

#include <btBulletDynamicsCommon.h>

#include <physics_prj/CollisionListener.h>
#include <physics_prj/PhysicsManager.h>
#include <utils_prj/KVector3.h>

namespace K_Engine {
	struct DynamicsWorld::CollisionCallBack : btOverlapFilterCallback {
		virtual bool needBroadphaseCollision(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1) const {
			bool collides = (proxy0->m_collisionFilterGroup & proxy1->m_collisionFilterMask) != 0;
			collides = collides && (proxy1->m_collisionFilterGroup & proxy0->m_collisionFilterMask);

			//add some additional logic here that modified 'collides'
			return collides;
		}
	};

	DynamicsWorld::DynamicsWorld(btVector3 const& gravity) {
		//Bullet initialisation.
		///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
		mCollisionConfig.reset(new btDefaultCollisionConfiguration());
		///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
		mDispatcher.reset(new btCollisionDispatcher(mCollisionConfig.get()));
		///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
		mSolver.reset(new btSequentialImpulseConstraintSolver());
		///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		mBroadphase.reset(new btDbvtBroadphase());

		btOverlapFilterCallback* filterCallback = new CollisionCallBack();

		btWorld_ = new btDiscreteDynamicsWorld(mDispatcher.get(), mBroadphase.get(), mSolver.get(), mCollisionConfig.get());
		btWorld_->setGravity(gravity);
		btWorld_->getPairCache()->setOverlapFilterCallback(filterCallback);

		collisionShapes = new btAlignedObjectArray<btCollisionShape*>();

		//mBtWorld->setInternalTickCallback(onTick); // FALTA IMPLEMENTAR ESTO
	}

	DynamicsWorld::~DynamicsWorld() {
		//cleanup in the reverse order of creation/initialization
		///-----cleanup_start-----
		//remove the rigidbodies from the dynamics world and delete them
		for (int i = btWorld_->getNumCollisionObjects() - 1; i >= 0; i--) {
			btCollisionObject* obj = btWorld_->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
				delete body->getMotionState();
			btWorld_->removeCollisionObject(obj);
			delete obj;
		}

		//delete collision shapes
		for (int j = 0; j < collisionShapes->size(); j++) {
			btCollisionShape* shape = (*collisionShapes)[j];
			(*collisionShapes)[j] = 0;
			delete shape;
		}

		collisionShapes->clear();
		delete collisionShapes; collisionShapes = nullptr;

		delete btWorld_;
		//The remaining objects are deleted by themselves as they are unique pointers
	}

	void DynamicsWorld::scaleCollisionShape(btRigidBody* rb, btVector3 const& scale) {
		btCollisionShape* cs = rb->getCollisionShape();
		cs->setLocalScaling(scale);
	}

	btRigidBody* DynamicsWorld::addRigidBody(ColliderType ct, const btTransform& transform, btVector3 const& dimensions, btVector3 const& size, BodyType bT, float mass, float restitution, float friction,
		int group, int mask, CollisionListener* colList) {
		btDefaultMotionState* state = new btDefaultMotionState(transform);
		btCollisionShape* cs = NULL;
		switch (ct) {
		case ColliderType::CT_BOX:
			cs = createBoxCollider(dimensions, size);
			break;
		case ColliderType::CT_SPHERE:
			cs = createSphereCollider(dimensions, size);
			break;
		}

		collisionShapes->push_back(cs);
		btVector3 inertia(0, 0, 0);

		switch (bT)
		{
		case BodyType::BT_DYNAMIC:
			cs->calculateLocalInertia(mass, inertia);
			break;
		case BodyType::BT_STATIC:
			break;
		}

		btRigidBody::btRigidBodyConstructionInfo bodyCI = btRigidBody::btRigidBodyConstructionInfo(mass, state, cs, inertia);
		bodyCI.m_restitution = restitution;
		bodyCI.m_friction = friction;

		auto rb = new btRigidBody(bodyCI);
		btWorld_->addRigidBody(rb, group, mask);

		if (colList != nullptr)
			rb->setUserPointer(colList);


		//btCollisionShape::setLocalScaling();

		return rb;
	}

	btBoxShape* DynamicsWorld::createBoxCollider(btVector3 const& dimensions, btVector3 const& scale) {
		auto shape = new btBoxShape(dimensions / 2.0f);
		shape->setLocalScaling(scale);
		return shape;
	}

	btSphereShape* DynamicsWorld::createSphereCollider(btVector3 const& radius, btVector3 const& scale) {
		auto shape = new btSphereShape(radius.x() / 2);
		shape->setLocalScaling(scale);
		return shape;;
	}
}
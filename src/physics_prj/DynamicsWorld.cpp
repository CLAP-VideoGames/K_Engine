#include "DynamicsWorld.h"
#include <btBulletDynamicsCommon.h>
#include "CollisionListener.h"
#include <CustomVector3.h>
#include "PhysicsManager.h"

struct DynamicsWorld::ColissionCallBack : btOverlapFilterCallback {
	virtual bool needBroadphaseCollision(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1) const {
		bool collides = (proxy0->m_collisionFilterGroup & proxy1->m_collisionFilterMask) != 0;
		collides = collides && (proxy1->m_collisionFilterGroup & proxy0->m_collisionFilterMask);

		//add some additional logic here that modified 'collides'
		return collides;
	}
};

DynamicsWorld::DynamicsWorld(btVector3 const& gravity){
	//Bullet initialisation.
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	mCollisionConfig.reset(new btDefaultCollisionConfiguration());
	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	mDispatcher.reset(new btCollisionDispatcher(mCollisionConfig.get()));
	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	mSolver.reset(new btSequentialImpulseConstraintSolver());
	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	mBroadphase.reset(new btDbvtBroadphase());

	btOverlapFilterCallback* filterCallback = new ColissionCallBack();

	btWorld_ = new btDiscreteDynamicsWorld(mDispatcher.get(), mBroadphase.get(), mSolver.get(), mCollisionConfig.get());
	btWorld_->setGravity(gravity);
	btWorld_->getPairCache()->setOverlapFilterCallback(filterCallback);

	collisionShapes = new btAlignedObjectArray<btCollisionShape*>();

	//mBtWorld->setInternalTickCallback(onTick); // FALTA IMPLEMENTAR ESTO
}

DynamicsWorld::~DynamicsWorld(){
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

btRigidBody* DynamicsWorld::addRigidBody(ColliderType ct, const btTransform& transform , btVector3 const& size, float mass, int group, int mask,
										 CollisionListener* colList){
	btDefaultMotionState* state = new btDefaultMotionState(transform);
	btCollisionShape* cs = NULL;
	switch (ct) {
		case ColliderType::CT_BOX:
			cs = createBoxCollider(size);
			break;
		case ColliderType::CT_SPHERE:
			cs = createSphereCollider(size);
			break;
	}

	collisionShapes->push_back(cs);

	btVector3 inertia(0, 0, 0);
	if (mass != 0) // mass = 0 -> static
		cs->calculateLocalInertia(mass, inertia);

	auto rb = new btRigidBody(mass, state, cs, inertia);
	btWorld_->addRigidBody(rb, group, mask);
	rb->setUserPointer(colList);
	
	return rb;
}

btBoxShape* DynamicsWorld::createBoxCollider(btVector3 const& size){
	auto shape = new btBoxShape((size / 2));
	shape->setLocalScaling(size);
	return shape;
}

btSphereShape* DynamicsWorld::createSphereCollider(btVector3 const& radius){
	auto shape = new btSphereShape(1.0f);
	shape->setLocalScaling(radius);
	return shape;;
}

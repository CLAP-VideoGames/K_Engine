#include "DynamicsWorld.h"
#include "CollisionListener.h"

#include <btBulletDynamicsCommon.h>
#include <CustomVector3.h>


DynamicsWorld::DynamicsWorld(btVector3 const& gravity){
	//Bullet initialisation.
	mCollisionConfig.reset(new btDefaultCollisionConfiguration());
	mDispatcher.reset(new btCollisionDispatcher(mCollisionConfig.get()));
	mSolver.reset(new btSequentialImpulseConstraintSolver());
	mBroadphase.reset(new btDbvtBroadphase());

	btWorld_ = new btDiscreteDynamicsWorld(mDispatcher.get(), mBroadphase.get(), mSolver.get(), mCollisionConfig.get());
	btWorld_->setGravity(gravity);
	
	collisionShapes = new btAlignedObjectArray<btCollisionShape*>();

	//mBtWorld->setInternalTickCallback(onTick); // FALTA IMPLEMENTAR ESTO
}

DynamicsWorld::~DynamicsWorld(){
	delete btWorld_;
}

btRigidBody* DynamicsWorld::addRigidBody(ColliderType ct, const btTransform& transform , btVector3 const& size, float mass, int group, int mask,
										 CollisionListener* colList){
	//void(*p)(void*, void* other, const btManifoldPoint & mnf), void* listener
	//auto node = ent->getParentSceneNode();
	btDefaultMotionState* state = new btDefaultMotionState(transform);

	btCollisionShape* cs = NULL;
	switch (ct)
	{
	case CT_BOX:
		cs = createBoxCollider(size);
		break;
	case CT_SPHERE:
		cs = createSphereCollider(size);
		break;
	//case CT_TRIMESH:
	//	//cs = StaticMeshToShapeConverter(ent).createTrimesh();
	//	break;
	//case CT_HULL:
	//	//cs = StaticMeshToShapeConverter(ent).createConvex();
	//	break;
	}

	collisionShapes->push_back(cs);

	btVector3 inertia(0, 0, 0);
	if (mass != 0) // mass = 0 -> static
		cs->calculateLocalInertia(mass, inertia);

	auto rb = new btRigidBody(mass, state, cs, inertia);
	//btWorld_->addRigidBody(rb);
	btWorld_->addRigidBody(rb, group, mask);
	//btBroadphaseProxy* b = rb->getBroadphaseProxy();
	//b->m_collisionFilterGroup = 
	//b->m_collisionFilterMask

	rb->setUserPointer(colList);
	
	//// transfer ownership to node
	//auto bodyWrapper = std::make_shared<RigidBody>(rb, mBtWorld);
	//node->getUserObjectBindings().setUserAny("BtRigidBody", bodyWrapper);
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

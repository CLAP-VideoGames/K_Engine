#include "PhysicsManager.h"
#include <btBulletDynamicsCommon.h>
#include "LinearMath/btTransform.h"
#include "DynamicsWorld.h"
#include "KVector3.h"

std::unique_ptr<PhysicsManager> PhysicsManager::instance = nullptr;

PhysicsManager::PhysicsManager() = default;

PhysicsManager::~PhysicsManager() = default;

PhysicsManager* PhysicsManager::GetInstance(){
	return instance.get();
}

bool PhysicsManager::Init(int numIterations, int step, const KVector3& gravity = KVector3(0, -9.8f, 0)){
	instance.reset(new PhysicsManager());
	btVector3 grav_ = { (btScalar)gravity.x, (btScalar)gravity.y, (btScalar)gravity.z };
	return instance.get()->initWorld(numIterations, step, grav_);
}

bool PhysicsManager::initWorld(int numIterations, int step, btVector3 const& gravity){
	bool succeed = true;
	try{
		this->gravity = new btVector3(gravity);
		dynamicsWorld_ = new DynamicsWorld(gravity);
		btWorld = dynamicsWorld_->getBtWorld();
		numIterations_ = numIterations;
	}
	catch (const std::exception&){
		succeed = false;
	}

	return succeed;
}

bool PhysicsManager::releaseWorld(){
	bool succeed = true;
	try{
		delete gravity;
		delete dynamicsWorld_; dynamicsWorld_ = nullptr;
	}
	catch (const std::exception&){
		succeed = false;
	}
	
	return succeed;
}

void PhysicsManager::update(){
	//for (int i = 0; i < numIterations_; i++) {
	btWorld->stepSimulation(1.f / 60.f, 10);

	
	//print positions of all objects
	for (int j = btWorld->getNumCollisionObjects() - 1; j >= 0; j--) {
		btCollisionObject* obj = btWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState()) {
			body->getMotionState()->getWorldTransform(trans);
		}
		else {
			trans = obj->getWorldTransform();
		}
		btScalar y;
		btScalar z;
		btScalar x;
		trans.getRotation().getEulerZYX(y, x, z);
	}
}

void PhysicsManager::exampleObjects(){
	//keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
	{
		//Forma del objeto en función del tipo
		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

		//collisionShapes->push_back(groundShape);

		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -56, 0));
		

		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass, localInertia);

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//body->getCollisionShape()
		//body->getWorldTransform();

		//add the body to the dynamics world
		btWorld->addRigidBody(body);
	}

	//the ground is a cube of side 100 at position y = -56.
	//the sphere will hit it at y = -6, with center at -5
	{
		//create a dynamic rigidbody

		//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
		btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		//btWorld->push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass(1.f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass, localInertia);

		startTransform.setOrigin(btVector3(2, 10, 0));

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		btWorld->addRigidBody(body);
	}
}

void PhysicsManager::changeCollisionFiltering(btRigidBody* rb, int group, int mask){
	btBroadphaseProxy* proxy = rb->getBroadphaseProxy();
	proxy->m_collisionFilterGroup = group;
	proxy->m_collisionFilterMask = mask;
}

btTransform* PhysicsManager::createTransform(KVector3 const& position, KVector3 const& rotation) {
	btVector3 pos = { (btScalar)position.x, (btScalar)position.y, (btScalar)position.z };
	btVector3 rot = { (btScalar)btRadians(rotation.x), (btScalar)btRadians(rotation.y), (btScalar)btRadians(rotation.z) };

	btTransform* tr = new btTransform();
	tr->setIdentity();
	tr->setOrigin(pos);
	//tr->setBasis()
	
	tr->setRotation(btQuaternion(rot.x(), rot.y(), rot.z()));
	

	return tr;
}

void PhysicsManager::changeGravity(KVector3 const& gravity){
	btVector3 grav_ = { (btScalar)gravity.x, (btScalar)gravity.y, (btScalar)gravity.z };
	
	if (this->gravity != nullptr) *this->gravity = grav_;
	else this->gravity = new btVector3(grav_);
}

DynamicsWorld* PhysicsManager::getWorld() const{
	return dynamicsWorld_;
}

bool PhysicsManager::Shutdown(){
	bool exit = instance.get()->releaseWorld();
	instance.reset(nullptr);
	return exit;
}

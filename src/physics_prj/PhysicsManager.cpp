#include "PhysicsManager.h"
#include <btBulletDynamicsCommon.h>

std::unique_ptr<PhysicsManager> PhysicsManager::instance = nullptr;

struct PhysicsManager::ColissionCallBack : btOverlapFilterCallback {
	virtual bool needBroadphaseCollision(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1) const {
		bool collides = (proxy0->m_collisionFilterGroup & proxy1->m_collisionFilterMask) != 0;
		collides = collides && (proxy1->m_collisionFilterGroup & proxy0 -> m_collisionFilterMask);

		//add some additional logic here that modified 'collides'
		return collides;
	}
};

PhysicsManager::PhysicsManager() = default;

PhysicsManager::~PhysicsManager() = default;

PhysicsManager* PhysicsManager::GetInstance(){
	return instance.get();
}

bool PhysicsManager::Init(int numIterations, int step, const btVector3& gravity = btVector3(0, -9.8f, 0)){
	instance.reset(new PhysicsManager());
	return instance.get()->initWorld(numIterations, step, gravity);
}

bool PhysicsManager::initWorld(int numIterations, int step, const btVector3& gravity){
	bool succeed = true;
	try{
		///-----initialization_start-----
		///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
		numIterations_ = numIterations;
		collisionConfiguration = new btDefaultCollisionConfiguration();

		///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
		dispatcher = new btCollisionDispatcher(collisionConfiguration);

		///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		overlappingPairCache = new btDbvtBroadphase();

		btOverlapFilterCallback* filterCallback = new ColissionCallBack();

		///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
		solver = new btSequentialImpulseConstraintSolver;

		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

		dynamicsWorld->setGravity(gravity);

		dynamicsWorld->getPairCache()->setOverlapFilterCallback(filterCallback);

		collisionShapes = new btAlignedObjectArray<btCollisionShape*>();
	}
	catch (const std::exception&){
		succeed = false;
	}

	return succeed;
}

bool PhysicsManager::releaseWorld(){
	bool succeed = true;
	
	try{
		//cleanup in the reverse order of creation/initialization
		///-----cleanup_start-----
		//remove the rigidbodies from the dynamics world and delete them
		for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) {
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
				delete body->getMotionState();
			dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}

		//delete collision shapes
		for (int j = 0; j < collisionShapes->size(); j++) {
			btCollisionShape* shape = (*collisionShapes)[j];
			(*collisionShapes)[j] = 0;
			delete shape;
		}

		//delete objects
		delete dynamicsWorld; dynamicsWorld = nullptr;
		delete solver; solver = nullptr;
		delete overlappingPairCache; overlappingPairCache = nullptr;
		delete dispatcher; dispatcher = nullptr;
		delete collisionConfiguration; collisionConfiguration = nullptr;
		collisionShapes->clear();
		delete collisionShapes; collisionShapes = nullptr;
	}
	catch (const std::exception&){
		succeed = false;
	}
	
	return succeed;
}

void PhysicsManager::update(){
	for (int i = 0; i < numIterations_; i++) {
		dynamicsWorld->stepSimulation(1.f / 60.f, 10);

		//print positions of all objects
		for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--) {
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;
			if (body && body->getMotionState()) {
				body->getMotionState()->getWorldTransform(trans);
			}
			else {
				trans = obj->getWorldTransform();
			}
			//printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
		}

		//system("CLS");
	}
}

void PhysicsManager::exampleObjects(){
	//keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
	{
		//Forma del objeto en función del tipo
		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

		collisionShapes->push_back(groundShape);

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
		dynamicsWorld->addRigidBody(body);
	}

	//the ground is a cube of side 100 at position y = -56.
	//the sphere will hit it at y = -6, with center at -5
	{
		//create a dynamic rigidbody

		//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
		btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		collisionShapes->push_back(colShape);

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

		dynamicsWorld->addRigidBody(body);
	}
}

bool PhysicsManager::Shutdown(){
	bool exit = instance.get()->releaseWorld();
	instance.reset(nullptr);
	return exit;
}

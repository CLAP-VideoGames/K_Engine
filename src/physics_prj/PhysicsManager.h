
#include <memory>

template<typename T>
class btAlignedObjectArray;

class btCollisionShape;
class btDiscreteDynamicsWorld;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;

class btVector3;

class PhysicsManager{

public:
	static PhysicsManager* getInstance();

	void init(int numIterations, int step, const btVector3& gravity);
	void update();
	void exampleObjects();
	void shutdown();
	~PhysicsManager();

private:
	static std::unique_ptr<PhysicsManager> instance;

	btDiscreteDynamicsWorld* dynamicsWorld;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btAlignedObjectArray<btCollisionShape*>* collisionShapes;
	btCollisionDispatcher* dispatcher; 
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btVector3* gravity;

	int numIterations_;
};


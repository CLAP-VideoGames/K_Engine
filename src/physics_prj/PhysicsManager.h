
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
	PhysicsManager();
	~PhysicsManager();

	static PhysicsManager* GetInstance();

	static bool Init(int numIterations, int step, const btVector3& gravity);
	static bool Shutdown();

	void update();
	void exampleObjects();
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

	bool initWorld(int numIterations, int step, const btVector3& gravity);
	bool releaseWorld();
};


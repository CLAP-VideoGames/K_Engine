#pragma once
#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <memory>
#include <string>

class btVector3;
class btTransform;
class btRigidBody;
class btDynamicsWorld;

enum class ColliderType {
	CT_BOX,
	CT_SPHERE,
	CT_TRIMESH,
	CT_HULL
};

enum class BodyType {
	BT_STATIC,
	BT_DYNAMIC,
};


namespace K_Engine {

	class CollisionLayers;
	struct Vector3;
	class DynamicsWorld;

	class  __declspec(dllexport) PhysicsManager {
	public:


		struct CollisionCallBack;

		PhysicsManager();

		~PhysicsManager();

		/// <summary>
		///	returns an instance of the manager. It must've been initialized previously.
		/// </summary>
		/// <returns></returns>
		static PhysicsManager* GetInstance();

		/// <summary>
		/// Initialize the static manager instance.
		/// </summary>
		/// <param name="step">Number of physics steps by second</param>
		/// <param name="gravity">Gravity of the world</param>
		/// <returns>if has been succesful the initialization</returns>
		static bool Init(std::string n, const Vector3& gravity);

		/// <summary>
		/// Realease the world and all its objects.
		/// </summary>
		/// <returns>if has been succesful the shutdown</returns>
		static bool Shutdown();

		/// <summary>
		/// Updates all the physics objects.
		/// </summary>
		void update();

		/// <summary>
		/// Change the collision layer and group of a certain rigidbody.
		/// </summary>
		/// <param name="rb">Reference to the RigidBody</param>
		/// <param name="group">With which layers collides</param>
		/// <param name="name">Name of the mask which belongs</param>
		void changeCollisionFiltering(btRigidBody* rb, int group, std::string nameMask);

		/// <summary>
		/// Creates a simple physic transform, settint a given position and rotation.
		/// </summary>
		/// <param name="position"></param>
		/// <param name="rotation"></param>
		/// <returns>reference to the created transform</returns>
		btTransform* createTransform(Vector3 const& position, Vector3 const& offset, Vector3 const& rotation);

		/// <summary>
		/// Change the gravity of the physic world.
		/// </summary>
		/// <param name="grav"></param>
		void changeGravity(Vector3 const& grav);

		/// <summary>
		/// Returns a reference to the physics world.
		/// </summary>
		DynamicsWorld* getWorld() const;

		/// <summary>
		/// Returns the value of the mask
		/// </summary>
		/// <param name="name">Key name</param>
		int getLayerID(std::string name) const;

		/// <summary>
		/// Adds a new layer to the world. It can be accesed by its name.
		/// </summary>
		/// <param name="name">Key name</param>
		void addLayer(std::string name);


	private:
		static std::unique_ptr<PhysicsManager> instance;

		btVector3* gravity;
		btDynamicsWorld* btWorld;
		DynamicsWorld* dynamicsWorld_;
		CollisionLayers* colLayers_;

		std::string name;

		/// <summary>
		/// Initialize the world with the given parameters
		/// </summary>
		/// <param name="numIterations"></param>
		/// <param name="step"></param>
		/// <param name="gravity"></param>
		/// <returns></returns>
		bool initWorld(const btVector3& gravity);

		/// <summary>
		/// Realease the world and all its objects.
		/// </summary>
		/// <returns>if has been succesful the shutdown</returns>
		bool releaseWorld();
	};
}
#endif // PHYSICSMANAGER_H
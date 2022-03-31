#pragma once
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <ecs_prj/Component.h>

class btCollisionShape;
class btRigidBody;
class btTransform;
class btDefaultMotionState;

class RigidBodyState;
enum class ColliderType;
enum class BodyType;

namespace K_Engine {
	class DynamicsWorld;
	class Transform;
	struct Vector3;
	/// <summary>
	/// This componentn provides to the entity a physic behaviour. 
	/// </summary>
	class __declspec(dllexport) RigidBody : public Component
	{
	public:
		/// <summary>
		/// Required to be initialized properly in the Component Manager
		/// </summary>
		/// <param name="e">Entity to be attached to</param>
		RigidBody(Entity* e);

		/// <summary>
		/// Initialize the new component, creating a new physic object with the given attributes
		/// </summary>
		/// <param name="e">Entity to be attached to</param>
		/// <param name="type_">Collider shape type</param>
		/// <param name="bType_">Physics type, dynamic, static...</param>
		/// <param name="mass">Mass value</param>
		/// <param name="mask_">Layer which belongs to</param>
		/// <param name="group_">With which layers collides</param>
		RigidBody(Entity* e, ColliderType type_, BodyType bType_, float mass, int mask_ = 1, int group_ = 1, bool isTrigger_ = false);
		~RigidBody();

		//Required method for the component name
		static std::string GetId();

		/// <summary>
		/// Determines whether is a trigger or not
		/// </summary>
		void setTrigger(bool value);

		/// <summary>
		/// Rotation restrictions
		/// </summary>
		/// <param name="i">Index of each axis. x, y, z respectively</param>
		/// <param name="value">wheters is blocked or not</param>
		void setRotConstraints(int i, bool value);
		/// <summary>
		/// Position restrictions
		/// </summary>
		/// <param name="i">Index of each axis. x, y, z respectively</param>
		/// <param name="value">wheters is blocked or not</param>
		void setPosConstraints(int i, bool value);

		/// <summary>
		/// Bounciness factor
		/// </summary>
		/// <param name="value"></param>
		void setRestitution(float value);

		/// <summary>
		/// Friction factor.
		/// </summary>
		/// <param name="value"></param>
		void setFriction(float value);

		/// <summary>
		/// It's called at the beginning of the execution.
		/// </summary>
		virtual void start();

		/// <summary>
		/// It's called every frame of the game.
		/// </summary> 
		virtual void update();

		/// <summary>
		/// Custom method for debugging.
		/// </summary>
		virtual void debug();

		/// <summary>
		/// Updates the physic scale which the transform scale
		/// </summary>
		void syncScale();

		/// <summary>
		/// Sets dimensions to the physics body. It's alien to the renderer size, but is still attached to
		/// its scale. Keep in mind that it's relative to its rotation.
		/// </summary>
		/// <param name="dimen">Dimensionsfvector</param>
		void setDimensions(Vector3 const& dimen);

		/// <summary>
		/// Sets dimensions to the physics body. It's alien to the renderer size, but is still attached to
		/// its scale.Keep in mind that it's relative to its rotation.
		/// </summary>
		/// <param name="dimen">Dimensions factor for all axis</param>
		void setDimensions(float d);

		/// <summary>
		/// Sets a distance from the Transform position. This will be the real physic position.
		/// Keep in mind that it is NOT relative to its rotation.
		/// </summary>
		void setOffset(Vector3 const& value);

	private:
		//Reference to transform Component
		Transform* transformRf_ = nullptr;
		//Mesh Type of the body
		ColliderType type_;
		//Body Physics Type
		BodyType bType_;
		//Reference to the world
		K_Engine::DynamicsWorld* world_ = nullptr;
		//Boolean to control if the associated trigger is a trigger or not (default is false)
		bool isTrigger = false;
		//Mass of the body
		float mass_;
		//Reference to bullet rigidbody
		btRigidBody* rb = nullptr;
		//Reference to the collision shape of this rigidbody
		btCollisionShape* rbShape = nullptr;
		//Reference to the default motion state of this rigidbody
		RigidBodyState* rbState = nullptr;
		//Reference to the physics transform of this rigidbody
		btTransform* btTransform_ = nullptr;
		//Required
		static std::string name;
		//Bounciness factor
		float restitution_;
		//Friction factor
		float friction_;
		//Array of constrains for rotation in x y z
		bool rotationConstraints[3]{ false, false, false };

		//Array of constrains for traslation in x y z
		bool positionConstraints[3]{ false, false, false };

		//Callbacks
		bool colisionando = false;
		void launchEnterCallbacks(void* entity);
		void launchStayCallbacks(void* entity);
		void launchExitCallbacks(void* entity);

		//Defines if the RigidBody is a trigger or not
		bool isTrigger_ = false;

		//Collision filtering
		int group_;
		int mask_;

		//Dimensions of the actual body
		Vector3* dimensions_;
		//Offset from the transform point. 
		Vector3* offsetCenter_;
	};
}
#endif RIGIDBODY_H
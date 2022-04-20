#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>

#include <ecs_prj/Component.h>

namespace K_Engine {
	class Vector3;

	/*
	* The Transform component is used to store information about our entity
	* This component is the place from where rigidBody and meshRenderer take the information
	* To use physics and to render our entities
	*/
	class __declspec(dllexport) Transform : public Component
	{
	public:

		Transform();

		/// <summary>
		/// Required to be initialized properly in the Component Manager
		/// </summary>
		/// <param name="e">Entity to be attached to</param>
		Transform(Entity* e);
		virtual ~Transform();

		static std::string GetId();

		virtual void init(K_Map* information);

		/// <summary>
		/// Moves the entity to a new positions relative to the current one.
		/// </summary>
		void translate(float x, float y, float z);

		/// <summary>
		/// Rotates the entity to a new rotation relative to the current one.
		/// </summary>
		void rotate(float x, float y, float z);
		/// <summary>
		/// Scales the entity to a new scale relative to the current one.
		/// </summary>
		void scale(float x, float y, float z);

		/// <summary>
		/// Sets the entity to a new position
		/// </summary>
		void setPosition(float x, float y, float z);
		/// <summary>
		/// Sets the entity to a new rotaion
		/// </summary>
		void setRotation(float x, float y, float z);
		/// <summary>
		/// Sets the entity to a new scale given its aixs values
		/// </summary>
		void setScale(float x, float y, float z);
		/// <summary>
		/// Sets the entity to a new scale given a global value for all its axis
		/// </summary>
		void setScale(float n);

		/// <summary>
		/// Gets the entity world position
		/// </summary>
		Vector3 getPosition() const;
		/// <summary>
		/// Gets the entity world rotation
		/// </summary>
		/// <returns></returns>
		Vector3 getRotation() const;
		/// <summary>
		/// Gets entity scale. It's ownself, relative to it.
		/// </summary>
		Vector3 getScale() const;

		/// <summary>
		/// Custom method for debugging.
		/// </summary>
		virtual void debug();

		/// <summary>
		/// It's called every frame of the game.
		/// </summary>
		virtual void update(int frameTime);

	private:
		static std::string name;

		//Arrays initialized to default values
		// x y z axis, in that order of our 3 main information arrays
		Vector3* position_;
		Vector3* rotation_;
		Vector3* scale_;
		Vector3* dimensions_;

		//for testing
		float timer = 10.0;
		float time;
		bool test = false; 
		int times = 0;
		int limitTimes = 30;
		int factor = 1;
	};
}
#endif // TRANSFORM_H
#pragma once
#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <ecs_prj/Component.h>

namespace Ogre {
	class SceneNode;
	class Entity;
	class Quaternion;
}

namespace K_Engine {
	class Transform;
	struct Vector3;
	/*
	* MeshRender is the component used to add diferent model to our entities
	* It takes the information of the model position scale and rotation from transform
	*/
	class __declspec(dllexport) MeshRenderer : public Component
	{
	public:
		MeshRenderer();

		MeshRenderer(Entity* e);
		virtual ~MeshRenderer();

		//Required method for the component name
		static std::string GetId();

		virtual void debug();

		virtual void start();
		virtual void init(K_Map* information);
		virtual void update(int frameTime);

		virtual void onEnable();
		virtual void onDisable();

		//Setters
		void setVisible(bool value);
		void setMaterial(std::string nMaterial);
		void setMesh(std::string mesh);

		//Getters
		Ogre::SceneNode* getOgreNode();
		Ogre::Entity* getOgreEntity();
		
		Ogre::Quaternion EulerToQuaternion(Vector3 const& rot);
		void syncScale();
		
		void syncRotation();

		void syncPosition();

		std::string getMeshName();

	private:
		// required
		static std::string name;

		// reference to tranform Component
		Transform* transformRf;

		// reference to the object's node & entity
		Ogre::SceneNode* mNode;
		Ogre::Entity* mEntity;

		bool visible;		  // visibility of the object
		std::string material; // name of the object's material
		std::string meshFile; //name of mesh file 
	};
}
#endif // MESHRENDERER_H
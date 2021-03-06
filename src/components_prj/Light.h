#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <utils_prj/Vector3.h>

#include <ecs_prj/Component.h>

namespace Ogre {
	class Light;
	class SceneNode;
}

namespace K_Engine {
	class Transform;

	enum class LightType;

	class __declspec(dllexport) Light : public Component {
	public:
		Light();

		/// <summary>
		/// Required to be initialized properly in the Component Manager
		/// </summary>
		/// <param name="e">Entity to be attached to</param>
		Light(Entity* e);
		Light(Entity* e, LightType lType, bool enable, Vector3* diff, Vector3* look);

		virtual ~Light();

		//Required method for the component name
		static std::string GetId();

		virtual void init(K_Map* information);

		/// <summary>
		/// It's called at the beginning of the execution.
		/// </summary>
		virtual void start();

		void changeType(LightType type);
		void changeDiffuse(Vector3 newDiff);

		void setVisible(bool visible);
		bool isVisible();

	private:
		//Required
		static std::string name;

		Ogre::SceneNode* mNode;
		Ogre::Light* mLight;

		Transform* transformRf_;

		LightType type;
		bool visible;

		Vector3* diffuse;
		Vector3* lookAt;

		// spotlight parameters
		float innerAngle, outerAngle;

		void setSpotlightParameters(float inAng, float outAng);
	};
}
#endif // LIGHT_H
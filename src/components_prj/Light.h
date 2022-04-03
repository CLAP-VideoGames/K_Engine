#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <ecs_prj/Component.h>

namespace Ogre {
	class Light;
	class SceneNode;
}

namespace K_Engine {
	class Vector3;

	enum class LightType;

	class __declspec(dllexport) Light : public Component {
	public:
		/// <summary>
		/// Required to be initialized properly in the Component Manager
		/// </summary>
		/// <param name="e">Entity to be attached to</param>
		Light(Entity* e);
		Light(Entity* e, LightType type, bool enabled);
		~Light();

		//Required method for the component name
		static std::string GetId();

		/// <summary>
		/// It's called at the beginning of the execution.
		/// </summary>
		virtual void start();

		void setVisible(bool visible);
		bool isVisible();

		/// <summary>
		/// Custom method for debugging.
		/// </summary>
		//virtual void debug();

	private:
		//Required
		static std::string name;

		Ogre::SceneNode* mNode;
		Ogre::Light* mLight;

		LightType type;

		bool visible;

		/*Vector3 diffuseColor_;
		Vector3 specularColor_;
		Vector3 direction_;*/

		//float distance_;

		// spotlight parameters
		float innerAngle, outerAngle;
	};
}
#endif // LIGHT_H
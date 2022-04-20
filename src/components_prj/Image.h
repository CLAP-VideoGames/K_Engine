#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <ecs_prj/Component.h>

namespace K_Engine {
	class UIManager;
	class UIImage;
	class Transform;
	/// <summary>
	/// This class provides an entity with a UiImage component
	/// </summary>
	class __declspec(dllexport) Image : public Component
	{
	public:

		Image();

		/// <summary>
		/// Required to be initialized properly in the Component Manager
		/// </summary>
		/// <param name="e">Entity to be attached to</param>
		Image(Entity* e);

		/// <summary>
		/// Creates an image with the specified name. The image material must be previously loaded.
		/// </summary>
		/// <param name="e">Entity to be attached</param>
		/// <param name="overlayName">Name of the element</param>
		/// <param name="imageName">Name of the image material</param>
		Image(Entity* e, std::string overlayName, std::string imageName);
		virtual ~Image();

		//Required method for the component name
		static std::string GetId();

		/// <summary>
		/// It's called at the beginning of the execution.
		/// </summary>
		virtual void start();

		/// <summary>
		/// It's called every frame of the game.
		/// </summary> 
		virtual void update(int frameTime);

	private:
		//Required
		static std::string name;

		//Reference to transform Component
		Transform* transformRf_ = nullptr;

		//Image created in UIManager
		UIImage* image_;

		//Basic attributes needed for the image
		std::string overlayName_;
		std::string imageName_;
	};
}


#endif IMAGE_H
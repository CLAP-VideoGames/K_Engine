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
		Image(Entity* e, std::string overlayName, std::string name);

		virtual ~Image();

		// required method for the component name
		static std::string GetId();

		virtual void init(K_Map* information);

		virtual void onEnable();

		virtual void onDisable();

		// It's called at the beginning of the execution.
		virtual void start();

		// It's called every frame of the game.
		virtual void update(int frameTime);

		void setInteractive(bool interactive);

		bool getIsFocus();

		void setDimensions(int width, int height);

	private:
		//Required
		static std::string name;

		Transform* transformRf_; // Reference to transform Component
		UIImage* image_;         // Image created in UIManager

		// Basic attributes needed for the image
		std::string overlayName_;
		std::string imageName_;

		bool interactive_;

		int width_;
		int height_;

		void syncData();
	};
}
#endif IMAGE_H
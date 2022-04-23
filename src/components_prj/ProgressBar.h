#pragma once
#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <ecs_prj/Component.h>

namespace K_Engine {
	class UIManager;
	class UIProgressBar;
	class Transform;
	/// <summary>
	/// This class provides an entity with a UiProgressBar component
	/// </summary>
	class __declspec(dllexport) ProgressBar : public Component
	{
	public:

		ProgressBar();

		/// <summary>
		/// Required to be initialized properly in the Component Manager
		/// </summary>
		/// <param name="e">Entity to be attached to</param>
		ProgressBar(Entity* e);

		/// <summary>
		/// Creates a progress bar with the specified name. The image material must be previously loaded.
		/// </summary>
		/// <param name="e">Entity to be attached</param>
		/// <param name="overlayName">Name of the element</param>
		/// <param name="imageName">Name of the image material</param>
		ProgressBar(Entity* e, std::string overlayName, std::string imageName, int x, int y, int orgWidth, int orgHeight, float progress = 100, float maxProgress = 100);
		virtual ~ProgressBar();

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

		/// <summary>
		/// Sets the actual progress in the ProgressBar
		/// </summary>
		/// <param name="progress">Actual progress (100 is 100% progress by default)</param>
		void setProgress(float progress);

		/// <summary>
		/// Sets the max value in the ProgressBar
		/// </summary>
		/// <param name="maxProgress">Value to be used as max progress</param>
		void setMaxProgress(float maxProgress);

	private:
		//Required
		static std::string name;

		//Reference to transform Component
		Transform* transformRf_ = nullptr;

		//ProgressBar created in UIManager
		UIProgressBar* progressBar_;

		//Basic attributes needed for the progress bar
		std::string overlayName_;
		std::string imageName_;
		int x_;
		int y_;
		int orgWidth_;
		int orgHeight_;
		float progress_;
		float maxProgress_;
	};
}


#endif PROGRESSBAR_H
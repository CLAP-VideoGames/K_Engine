#include "ProgressBar.h"

#include <ecs_prj/Entity.h>

#include <components_prj/Transform.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UiProgressBar.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

namespace K_Engine {
	//Required
	std::string ProgressBar::name = "ProgressBar";

	ProgressBar::ProgressBar() : Component() {
	}

	K_Engine::ProgressBar::ProgressBar(Entity* e) : Component( e){
	}

	ProgressBar::ProgressBar(Entity* e, std::string overlayName, std::string imageName, float progress, float maxProgress) : Component( e)
	{
		overlayName_ = overlayName;
		imageName_ = imageName;
		progress_ = progress;
		maxProgress_ = maxProgress;
	}

	K_Engine::ProgressBar::~ProgressBar() = default;

	std::string K_Engine::ProgressBar::GetId()
	{
		return name;
	}

	void K_Engine::ProgressBar::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		progressBar_ = UIManager::GetInstance()->addProgressBar(overlayName_, imageName_);
		progressBar_->setMaterial(imageName_);
		progressBar_->setMaxProgress(maxProgress_);
		progressBar_->setProgress(progress_);
	}
	void ProgressBar::update(int frameTime)
	{
		//Position syncing
		Vector3 pos = transformRf_->getPosition();
		progressBar_->setPosition(transformRf_->getPosition().x, transformRf_->getPosition().y);

		//Scale syincing
		progressBar_->setSize(progressBar_->getSize().first * transformRf_->getScale().x, progressBar_->getSize().second * transformRf_->getScale().y);
		
		//ZOrder syncing
		progressBar_->setRenderOrder(transformRf_->getPosition().z);
	}
	void ProgressBar::setProgress(float progress)
	{
		progressBar_->setProgress(progress);
	}
	void ProgressBar::setMaxProgress(float maxProgress)
	{
		progressBar_->setMaxProgress(maxProgress);
	}
}
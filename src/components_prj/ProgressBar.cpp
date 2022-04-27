#include "ProgressBar.h"

#include <ecs_prj/Entity.h>

#include <components_prj/Transform.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UIProgressBar.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

#include <utils_prj/K_Map.h>

namespace K_Engine {
	//Required
	std::string ProgressBar::name = "ProgressBar";

	std::string K_Engine::ProgressBar::GetId() {
		return name;
	}

	void ProgressBar::init(K_Map* information)
	{
		overlayName_ = information->value("overlayName");
		imageName_ = information->value("imageName");
		x_ = information->valueToNumber("x");
		y_ = information->valueToNumber("y");
		orgWidth_ = information->valueToNumber("orgWidth");
		orgHeight_ = information->valueToNumber("orgHeight");
		progress_ = information->valueToNumber("progress");
		maxProgress_ = information->valueToNumber("maxProgress");
	}

	ProgressBar::ProgressBar() : Component() {}

	K_Engine::ProgressBar::ProgressBar(Entity* e) : Component(e) {}

	ProgressBar::ProgressBar(Entity* e, std::string overlayName, std::string imageName, int x, int y,
		int orgWidth, int orgHeight, float progress, float maxProgress) : Component(e) {
		overlayName_ = overlayName;
		imageName_ = imageName;
		x_ = x;
		y_ = y;
		orgWidth_ = orgWidth;
		orgHeight_ = orgHeight;
		progress_ = progress;
		maxProgress_ = maxProgress;
	}

	K_Engine::ProgressBar::~ProgressBar() = default;

	void K_Engine::ProgressBar::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		progressBar_ = UIManager::GetInstance()->addWidget<UIProgressBar>(overlayName_, imageName_, x_, y_, orgWidth_, orgHeight_);
		progressBar_->setMaterial(imageName_);
		progressBar_->setMaxProgress(maxProgress_);
		progressBar_->setProgress(progress_);
	}

	void ProgressBar::update(int frameTime)
	{
		////Position syncing
		//Vector3 pos = transformRf_->getPosition();
		//progressBar_->setPosition(transformRf_->getPosition().x, transformRf_->getPosition().y);

		////Scale syincing
		//progressBar_->setSize(progressBar_->getSize().first * transformRf_->getScale().x, progressBar_->getSize().second * transformRf_->getScale().y);
		//
		////ZOrder syncing
		//progressBar_->setRenderOrder(transformRf_->getPosition().z);
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
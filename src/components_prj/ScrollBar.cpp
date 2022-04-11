#include "ScrollBar.h"

#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UiScrollBar.h>

#include <utils_prj/Vector3.h>

namespace K_Engine {
	//Required
	std::string ScrollBar::name = "ScrollBar";

	K_Engine::ScrollBar::ScrollBar(Entity* e) : Component("ScrollBar", e)
	{
		name = id;
	}

	ScrollBar::ScrollBar(Entity* e, std::string overlayName, std::string imageName, int upperLimit, int lowerLimit) : Component("ScrollBar", e)
	{
		name = id;
		overlayName_ = overlayName;
		imageName_ = imageName;
		upperLimit_ = upperLimit;
		lowerLimit_ = lowerLimit;
	}

	K_Engine::ScrollBar::~ScrollBar() = default;

	std::string K_Engine::ScrollBar::GetId()
	{
		return name;
	}

	void K_Engine::ScrollBar::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		scrollBar_ = UIManager::GetInstance()->addScrollBar(overlayName_, imageName_, upperLimit_, lowerLimit_);
	}
	void ScrollBar::update(int frameTime)
	{
		//Position syncing
		/*Vector3 pos = transformRf_->getPosition();
		scrollBar_->setPosition(transformRf_->getPosition().x, transformRf_->getPosition().y);*/

		//Scale syincing
		/*scrollBar_->setSize(scrollBar_->getSize().first * transformRf_->getScale().x, scrollBar_->getSize().second * transformRf_->getScale().y);*/

		//ZOrder syncing
		/*scrollBar_->setRenderOrder(transformRf_->getPosition().z);*/
	}
}
#include "ScrollBar.h"

#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UiScrollBar.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

namespace K_Engine {
	//Required
	std::string ScrollBar::name = "ScrollBar";

	ScrollBar::ScrollBar() : Component() {
	}

	K_Engine::ScrollBar::ScrollBar(Entity* e) : Component( e){
	}

	ScrollBar::ScrollBar(Entity* e, std::string overlayName, std::string imageName, int x, int upperLimit, int lowerLimit) : Component(e)
	{
		overlayName_ = overlayName;
		imageName_ = imageName;
		x_ = x;
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
		scrollBar_ = UIManager::GetInstance()->addScrollBar(overlayName_, imageName_, x_, upperLimit_, lowerLimit_);
	}
	void ScrollBar::update(int frameTime)
	{
		//Position syncing
		//Transform actualization if there was a change in position
		//if (scrollBar_->getNeedsSync()) {
		//	transformRf_->setPosition(transformRf_->getPosition().x, scrollBar_->getPosition().second, transformRf_->getPosition().z);
		//	scrollBar_->setNeedsSync(false);
		//}

		//////Element actualization
		//scrollBar_->updatePosition(transformRf_->getPosition());

		//Scale syincing
		/*scrollBar_->setSize(scrollBar_->getSize().first * transformRf_->getScale().x, scrollBar_->getSize().second * transformRf_->getScale().y);*/

		//ZOrder syncing
		/*scrollBar_->setRenderOrder(transformRf_->getPosition().z);*/
	}
}
#include "ScrollBar.h"

#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UIScrollBar.h>
#include <ui_prj/Rectangle.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>
#include <utils_prj/K_Map.h>

#include <input_prj/InputManager.h>

namespace K_Engine {
	//Required
	std::string ScrollBar::name = "ScrollBar";

	std::string K_Engine::ScrollBar::GetId() {
		return name;
	}

	ScrollBar::ScrollBar() : Component() {}

	K_Engine::ScrollBar::ScrollBar(Entity* e) : Component(e) {}

	ScrollBar::ScrollBar(Entity* e, std::string overlayName, std::string imageName,
		int x, int upperLimit, int lowerLimit) : Component(e) {
		overlayName_ = overlayName;
		imageName_ = imageName;
		x_ = x;
		upperLimit_ = upperLimit;
		lowerLimit_ = lowerLimit;

		inputArea = new Rectangle();

		inputMan = K_Engine::InputManager::GetInstance();

		pressed_ = false;
	}

	K_Engine::ScrollBar::~ScrollBar() {
		delete inputArea; inputArea = nullptr;
	}

	void ScrollBar::init(K_Map* information)
	{
		overlayName_ = information->value("overlayName");
		imageName_ = information->value("imageName");
		x_ = information->valueToNumber("x");
		upperLimit_ = information->valueToNumber("upperLimit");
		lowerLimit_ = information->valueToNumber("lowerLimit");

		inputArea = new Rectangle();

		inputMan = K_Engine::InputManager::GetInstance();

		pressed_ = false;
	}

	void ScrollBar::onEnable()
	{
		if (scrollBar_ != nullptr)
			scrollBar_->show();
	}

	void ScrollBar::onDisable()
	{
		scrollBar_->hide();
	}

	void K_Engine::ScrollBar::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		scrollBar_ = UIManager::GetInstance()->addWidget<UIScrollBar>(overlayName_, imageName_, x_, upperLimit_, lowerLimit_);
	}

	void ScrollBar::update(int frameTime)
	{
		//Setup the input area rectangle
		inputArea->x = scrollBar_->getPosition().first; inputArea->y = scrollBar_->getPosition().second;
		inputArea->w = scrollBar_->getSize().first; inputArea->h = scrollBar_->getSize().second;

		Point pointer;
		auto pointPos = inputMan->getMousePos();
		pointer.x = pointPos.first;
		pointer.y = pointPos.second;

		if (inputMan->getLeftMouseButtonPressed())
		{
			if (PointInRect(&pointer, inputArea)) {
				pressed_ = true;
			}
		}
		else
			pressed_ = false;

		if (pressed_) {
			auto y = scrollBar_->getPosition().second;
			if (y >= upperLimit_ && y <= lowerLimit_) {
				if (pointer.y >= upperLimit_ && pointer.y <= lowerLimit_) {
					scrollBar_->setTop(pointer.y);
				}
			}
		}
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
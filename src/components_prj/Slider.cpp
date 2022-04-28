#include <components_prj/Slider.h>

#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UISlider.h>
#include <ui_prj/UIProgressBar.h>
#include <ui_prj/Rectangle.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

#include <input_prj/InputManager.h>
#include <utils_prj/K_Map.h>

namespace K_Engine {
	//Required
	std::string Slider::name = "Slider";

	std::string K_Engine::Slider::GetId() {
		return name;
	}

	void Slider::init(K_Map* information)
	{
		overlayName_ = information->value("overlayName");
		imageName_ = information->value("imageName");
		y_ = information->valueToNumber("y");
		leftLimit_ = information->valueToNumber("leftLimit");
		rightLimit_ = information->valueToNumber("rightLimit");

		inputArea = new Rectangle();

		inputMan = K_Engine::InputManager::GetInstance();

		pressed_ = false;
	}

	Slider::Slider() : Component() {}

	K_Engine::Slider::Slider(Entity* e) : Component(e) {}

	Slider::Slider(Entity* e, std::string overlayName, std::string imageName, int y, int leftLimit, int rightLimit) : Component(e) {
		overlayName_ = overlayName;
		imageName_ = imageName;

		y_ = y; leftLimit_ = leftLimit;
		rightLimit_ = rightLimit;

		inputArea = new Rectangle();

		inputMan = K_Engine::InputManager::GetInstance();

		pressed_ = false;
	}

	K_Engine::Slider::~Slider() {
		delete inputArea; inputArea = nullptr;
		delete progressBar_; progressBar_ = nullptr;
	}

	void K_Engine::Slider::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		slider_ = UIManager::GetInstance()->addWidget<UISlider>(overlayName_, imageName_, y_, leftLimit_, rightLimit_);
		slider_->setRenderOrder(40);

		progressBar_ = new UIProgressBar(overlayName_ + " progress", "DefaultProgressBar", leftLimit_, y_, rightLimit_-leftLimit_, 20);
		progressBar_->setMaxProgress(100);
		progressBar_->setProgress(100);
		progressBar_->setRenderOrder(30);

		background_ = new UIProgressBar(overlayName_ + " background", "GreenDefaultProgressBar", leftLimit_, y_, rightLimit_ - leftLimit_, 20);
		background_->setMaxProgress(100);
		background_->setProgress(100);
		background_->setRenderOrder(20);
	}

	void Slider::update(int frameTime)
	{
		//Setup the input area rectangle
		inputArea->x = slider_->getPosition().first; inputArea->y = slider_->getPosition().second;
		inputArea->w = slider_->getSize().first; inputArea->h = slider_->getSize().second;

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
			auto x = slider_->getPosition().first;
			if (x >= leftLimit_ && x <= rightLimit_) {
				if (pointer.x >= leftLimit_ && pointer.x <= rightLimit_ - slider_->getSize().first) {
					slider_->setLeft(pointer.x);
					progressBar_->setProgress(slider_->getRelativePos());
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
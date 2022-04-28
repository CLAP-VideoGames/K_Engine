#include <components_prj/Slider.h>

#include <components_prj/Transform.h>
#include <components_prj/ProgressBar.h>

#include <ecs_prj/Entity.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UISlider.h>
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
	}

	void Slider::init(K_Map* information)
	{
		overlayName_ = information->value("overlayName");
		imageName_ = information->value("imageName");
		width = information->valueToNumber("width");

		inputArea = new Rectangle();

		inputMan = K_Engine::InputManager::GetInstance();

		pressed_ = false;
	}

	void Slider::onEnable()
	{
		if (slider_ != nullptr)
			slider_->show();
	}

	void Slider::onDisable()
	{
		slider_->hide();
	}

	void K_Engine::Slider::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		leftLimit_ = transformRf_->getPosition().x;
		rightLimit_ = leftLimit_ + width;
		y_ = transformRf_->getPosition().y;
		slider_ = UIManager::GetInstance()->addWidget<UISlider>(overlayName_, imageName_, y_, leftLimit_, rightLimit_);

		progressBar_ = entity->addComponent<ProgressBar>(overlayName_ + " progress", "DefaultProgressBar", rightLimit_-leftLimit_, 20);
		progressBar_->setCustomRenderOrder(5);

		background_ = entity->addComponent<ProgressBar>(overlayName_ + " background", "GreenDefaultProgressBar", rightLimit_ - leftLimit_, 20);
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
		slider_->setLeft(transformRf_->getPosition().x + (slider_->getPosition().first - leftLimit_));
		slider_->setTop(transformRf_->getPosition().y);
		rightLimit_ = transformRf_->getPosition().x + (rightLimit_ - leftLimit_);
		leftLimit_ = transformRf_->getPosition().x;
		slider_->setLeftLimit(leftLimit_);
		slider_->setRightLimit(rightLimit_);

		//ZOrder syncing
		slider_->setRenderOrder(transformRf_->getPosition().z + 10);
	}
}
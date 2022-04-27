#include "Button.h"

#include <ecs_prj/Entity.h>

#include <components_prj/Transform.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UIButton.h>
#include <ui_prj/Rectangle.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

#include <input_prj/InputManager.h>

#include <utils_prj/K_Map.h>

namespace K_Engine {
	//Required
	std::string Button::name = "Button";

	std::string Button::GetId() {
		return name;
	}

	Button::Button() : Component() {}

	K_Engine::Button::Button(Entity* e) : Component(e) {}

	Button::Button(Entity* e, std::string overlayName, std::string imageName,
		std::string hoverImageName, std::string pressedImageName) : Component(e) {
		overlayName_ = overlayName;
		imageName_ = imageName;

		hoverImageName_ = hoverImageName;
		pressedImageName_ = pressedImageName;

		inputArea = new Rectangle();

		inputMan = K_Engine::InputManager::GetInstance();
	}

	Button::~Button() {
		delete inputArea; inputArea = nullptr;
	};

	void Button::init(K_Map* information)
	{
		overlayName_ = information->value("overlayName");
		imageName_ = information->value("imageName");

		hoverImageName_ = information->value("hoverImageName");
		pressedImageName_ = information->value("pressedImageName");

		keyCallback_ = information->value("onClick");
		setButtonClick(information->valueToCallback(keyCallback_));

		inputArea = new Rectangle();

		inputMan = K_Engine::InputManager::GetInstance();
	}

	void K_Engine::Button::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		button_ = UIManager::GetInstance()->addWidget<UIButton>(overlayName_, imageName_, hoverImageName_, pressedImageName_);
		//Scale syincing
		button_->setSize(button_->getSize().first * transformRf_->getScale().x, button_->getSize().second * transformRf_->getScale().y);
		
		inputArea->h = button_->getHeight();
		inputArea->w = button_->getWidth();
		inputArea->x = button_->getLeft();
		inputArea->y = button_->getTop();
	}

	void Button::update(int frameTime)
	{
		inputArea->h = button_->getHeight();
		inputArea->w = button_->getWidth();
		inputArea->x = button_->getLeft();
		inputArea->y = button_->getTop();

		Point pointer;
		auto pointPos = inputMan->getMousePos();
		pointer.x = pointPos.first;
		pointer.y = pointPos.second;

		pressed_ = false;

		if (PointInRect(&pointer, inputArea)) {

			if (inputMan->getLeftMouseButtonPressed()) {
				pressed_ = true;

				button_->setMaterial(pressedImageName_);
			}
			else button_->setMaterial(hoverImageName_);
		}
		else button_->setMaterial(imageName_);


		//Position syncing
		Vector3 pos = transformRf_->getPosition();
		button_->setPosition(transformRf_->getPosition().x, transformRf_->getPosition().y);

		//ZOrder syncing
		button_->setRenderOrder(transformRf_->getPosition().z);

		//Callback check
		if (pressed_) {
			if (onButtonClick != nullptr) {
				onButtonClick(keyCallback_);
			}
		}
	}
	void Button::setButtonClick(std::function<void(std::string)> function)
	{
		onButtonClick = function;
	}
}
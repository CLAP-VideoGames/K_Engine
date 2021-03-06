#include "Button.h"

#include <iostream>

#include <ecs_prj/Entity.h>

#include <components_prj/Transform.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UIButton.h>
#include <ui_prj/Rectangle.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

#include <input_prj/InputManager.h>
#include <render_prj/RenderManager.h>

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
		std::string hoverImageName, std::string pressedImageName, float width, float height) : Component(e) {
		overlayName_ = overlayName;
		imageName_ = imageName;
		hoverImageName_ = hoverImageName;
		pressedImageName_ = pressedImageName;
		width_ = width;
		height_ = height;

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
		width_ = information->valueToNumber("width");
		height_ = information->valueToNumber("height");

		keyCallback_ = information->value("onClick");
		setButtonClick(information->valueToCallback(keyCallback_));

		inputArea = new Rectangle();
		inputMan = K_Engine::InputManager::GetInstance();
	}

	void Button::onEnable() {
		if (button_ != nullptr)
			button_->show();
	}

	void Button::onDisable() {
		button_->hide();
	}

	void K_Engine::Button::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		button_ = UIManager::GetInstance()->addWidget<UIButton>(overlayName_, imageName_, hoverImageName_, pressedImageName_);
		button_->setSize(width_, height_);
		button_->setInteractive(true);

		syncData();
	}

	void Button::update(int frameTime)
	{
		syncData();

		//Gamepad control
		if (button_->getIsFocusNow()) {
			if (inputMan->controllerButtonPressed(CONTROLLER_BUTTON_A)) {
				button_->setMaterial(pressedImageName_);
				onButtonClick(keyCallback_);
			}
		}

		//Mouse control
		Point pointer; auto pointPos = inputMan->getMousePos();
		pointer.x = pointPos.first; pointer.y = pointPos.second;

		pressed_ = false;
		if (PointInRect(&pointer, inputArea)) {
			if (inputMan->getLeftMouseButtonPressed()) {
				pressed_ = true;
				button_->setMaterial(pressedImageName_);
				if (onButtonClick != nullptr) 
					onButtonClick(keyCallback_);
			}
			else button_->setMaterial(hoverImageName_);
		}
		else button_->setMaterial(imageName_);
	}
	
	void Button::setButtonClick(std::function<void(std::string)> function) {
		onButtonClick = function;
	}

	void Button::setDimensions(float width, float height)
	{
		if (button_ != nullptr) {
			button_->setSize(width, height);
			width_ = width;
			height_ = height;
		}
		else {
			width_ = width;
			height_ = height;
		}
	}

	void Button::syncData() {
		// Position syncing
		button_->setPosition(transformRf_->getPosition().x, transformRf_->getPosition().y);
		// Size syncing
		button_->setSize(button_->getSize().first * transformRf_->getScale().x, button_->getSize().second * transformRf_->getScale().y);
		// ZOrder syncing
		button_->setRenderOrder((int)transformRf_->getPosition().z);

		inputArea->x = button_->getPosition().first * RenderManager::GetInstance()->windowWidth(); 
		inputArea->y = button_->getPosition().second * RenderManager::GetInstance()->windowHeight();
		inputArea->w = button_->getSize().first * RenderManager::GetInstance()->windowWidth(); 
		inputArea->h = button_->getSize().second * RenderManager::GetInstance()->windowHeight();
	}
}
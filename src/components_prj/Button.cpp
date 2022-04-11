#include "Button.h"

#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UiButton.h>

#include <utils_prj/Vector3.h>

namespace K_Engine {
	//Required
	std::string Button::name = "Button";

	K_Engine::Button::Button(Entity* e) : Component("Button", e)
	{
		name = id;
	}

	Button::Button(Entity* e, std::string overlayName, std::string imageName, std::string hoverImageName, std::string pressedImageName) : Component("Button", e)
	{
		name = id;
		overlayName_ = overlayName;
		imageName_ = imageName;

		hoverImageName_ = hoverImageName;
		pressedImageName_ = pressedImageName;
	}

	K_Engine::Button::~Button() = default;

	std::string K_Engine::Button::GetId()
	{
		return name;
	}

	void K_Engine::Button::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		button_ = UIManager::GetInstance()->addButton(overlayName_, imageName_, hoverImageName_, pressedImageName_);
	}
	void Button::update(int frameTime)
	{
		//Position syncing
		Vector3 pos = transformRf_->getPosition();
		button_->setPosition(transformRf_->getPosition().x, transformRf_->getPosition().y);

		//Scale syincing
		button_->setSize(button_->getSize().first * transformRf_->getScale().x, button_->getSize().second * transformRf_->getScale().y);

		//Callback check
		if (button_->getPressed()) {
			if (onButtonClick != nullptr) {
				onButtonClick;
			}
		}
	}
	void Button::setButtonClick(std::function<void(void*)> function)
	{
		onButtonClick = function;
	}
}
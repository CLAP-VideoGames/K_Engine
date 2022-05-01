#include "Focus.h"

#include <ecs_prj/Entity.h>

#include <components_prj/Transform.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UIImage.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

#include <utils_prj/K_Map.h>
#include <utils_prj/Timer.h>

#include <input_prj/InputManager.h>

namespace K_Engine {
	//Required
	std::string Focus::name = "Focus";

	std::string Focus::GetId() {
		return name;
	}

	Focus::Focus() : Component() {}

	Focus::Focus(Entity* e) : Component(e) {}

	Focus::Focus(Entity* e, std::string overlayName, std::string imageName) : Component(e) {
		overlayName_ = overlayName;
		imageName_ = imageName;

		inputMan = K_Engine::InputManager::GetInstance();
		uiManager = K_Engine::UIManager::GetInstance();

		timerToUpdate = new Timer();

		imageOffset = 100;
		canChangeFocus_ = true;
	}

	Focus::~Focus() {
		delete timerToUpdate;
		timerToUpdate = nullptr;
	}

	void Focus::init(K_Map* information)
	{
		overlayName_ = information->value("overlayName");
		imageName_ = information->value("imageName");

		inputMan = K_Engine::InputManager::GetInstance();
		uiManager = K_Engine::UIManager::GetInstance();

		timerToUpdate = new Timer();

		imageOffset = 100;
		canChangeFocus_ = true;
	}

	void Focus::onDisable()
	{
		image_->setLeft(0);
		image_->setTop(0);
		transformRf_->setPosition(0, 0, transformRf_->getPosition().z);
		image_->hide();
		canChangeFocus_ = true;
	}

	void Focus::start()
	{
		transformRf_ = entity->getComponent<Transform>();

		image_ = UIManager::GetInstance()->addWidget<UIImage>(overlayName_, imageName_);
		image_->hide();

		timerToUpdate->reset();

		syncData();
	}

	void Focus::update(int frameTime) {
		if (timerToUpdate->currTime() > 200) {
			processMovement();
			timerToUpdate->reset();
		}

		syncData();
	}

	void Focus::syncData()
	{
		// Position syncing
		image_->setPosition(transformRf_->getPosition().x, transformRf_->getPosition().y);
		// Size syncing
		image_->setSize(image_->getSize().first * transformRf_->getScale().x, image_->getSize().second * transformRf_->getScale().y);
		// ZOrder syncing
		image_->setRenderOrder((int)transformRf_->getPosition().z);
	}
	void Focus::processMovement()
	{
		if (canChangeFocus_) {
			if (inputMan->controllerAxisValue(CONTROLLER_AXIS_LEFTX) != 0 ||
				inputMan->controllerButtonPressed(CONTROLLER_BUTTON_DPAD_LEFT) ||
				inputMan->controllerButtonPressed(CONTROLLER_BUTTON_DPAD_RIGHT)) {
				if (inputMan->controllerAxisValue(CONTROLLER_AXIS_LEFTX) < 0 ||
					inputMan->controllerButtonPressed(CONTROLLER_BUTTON_DPAD_LEFT)) {
					//Mover a la izquierda
					image_->show();
					UIElement* elementToMoveTo = uiManager->getNextFocusLeft(image_, imageOffset);
					if (elementToMoveTo != nullptr) {
						if (currentElement != nullptr)
							currentElement->setFocusNow(false);
						transformRf_->setPosition(elementToMoveTo->getPosition().first - imageOffset / 2,
							elementToMoveTo->getPosition().second - imageOffset / 2,
							transformRf_->getPosition().z);
						image_->setSize(elementToMoveTo->getSize().first + imageOffset, elementToMoveTo->getSize().second + imageOffset);
						elementToMoveTo->setFocusNow(true);
						currentElement = elementToMoveTo;
					}
				}
				else if (inputMan->controllerAxisValue(CONTROLLER_AXIS_LEFTX) > 0 ||
					inputMan->controllerButtonPressed(CONTROLLER_BUTTON_DPAD_RIGHT)) {
					//Mover a la derecha
					image_->show();
					UIElement* elementToMoveTo = uiManager->getNextFocusRight(image_, imageOffset);
					if (elementToMoveTo != nullptr) {
						if (currentElement != nullptr)
							currentElement->setFocusNow(false);
						transformRf_->setPosition(elementToMoveTo->getPosition().first - imageOffset / 2,
							elementToMoveTo->getPosition().second - imageOffset / 2,
							transformRf_->getPosition().z);
						image_->setSize(elementToMoveTo->getSize().first + imageOffset, elementToMoveTo->getSize().second + imageOffset);
						elementToMoveTo->setFocusNow(true);
						currentElement = elementToMoveTo;
					}
				}
			}
			else if (inputMan->controllerAxisValue(CONTROLLER_AXIS_LEFTY) != 0 ||
				inputMan->controllerButtonPressed(CONTROLLER_BUTTON_DPAD_UP) ||
				inputMan->controllerButtonPressed(CONTROLLER_BUTTON_DPAD_DOWN)) {
				if (inputMan->controllerAxisValue(CONTROLLER_AXIS_LEFTY) < 0 ||
					inputMan->controllerButtonPressed(CONTROLLER_BUTTON_DPAD_UP)) {
					//Mover arriba
					image_->show();
					UIElement* elementToMoveTo = uiManager->getNextFocusUp(image_, imageOffset);
					if (elementToMoveTo != nullptr) {
						if (currentElement != nullptr)
							currentElement->setFocusNow(false);
						transformRf_->setPosition(elementToMoveTo->getPosition().first - imageOffset / 2,
							elementToMoveTo->getPosition().second - imageOffset / 2,
							transformRf_->getPosition().z);
						image_->setSize(elementToMoveTo->getSize().first + imageOffset, elementToMoveTo->getSize().second + imageOffset);
						elementToMoveTo->setFocusNow(true);
						currentElement = elementToMoveTo;
					}
				}
				else if (inputMan->controllerAxisValue(CONTROLLER_AXIS_LEFTY) > 0 ||
					inputMan->controllerButtonPressed(CONTROLLER_BUTTON_DPAD_DOWN)) {
					//Mover abajo
					image_->show();
					UIElement* elementToMoveTo = uiManager->getNextFocusDown(image_, imageOffset);
					if (elementToMoveTo != nullptr) {
						if (currentElement != nullptr)
							currentElement->setFocusNow(false);
						transformRf_->setPosition(elementToMoveTo->getPosition().first - imageOffset / 2,
							elementToMoveTo->getPosition().second - imageOffset / 2,
							transformRf_->getPosition().z);
						image_->setSize(elementToMoveTo->getSize().first + imageOffset, elementToMoveTo->getSize().second + imageOffset);
						elementToMoveTo->setFocusNow(true);
						currentElement = elementToMoveTo;
					}
				}
			}
		}

		if (inputMan->controllerButtonPressed(CONTROLLER_BUTTON_A)) {
			canChangeFocus_ = !canChangeFocus_;
		}
		else {
			if (inputMan->controllerButtonPressed(CONTROLLER_BUTTON_B))
				canChangeFocus_ = true;
		}
	}
}
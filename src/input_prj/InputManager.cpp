#include "InputManager.h"

#include <iostream>

#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_scancode.h>
#include <SDL_keycode.h>
#include <SDL_gamecontroller.h>

std::unique_ptr<InputManager> InputManager::instance = nullptr;

InputManager::InputManager() = default;

InputManager::~InputManager() = default;

InputManager* InputManager::GetInstance()
{
	return instance.get();
}

bool InputManager::Init()
{
	instance.reset(new InputManager());

	instance.get()->kbState_ = SDL_GetKeyboardState(0);
	instance.get()->flush();

	Uint32 SDL_system_init = SDL_WasInit(SDL_INIT_EVERYTHING);
	if (!SDL_system_init)
		std::cout << "SDL not initialized\n";

	// controller = SDL_GameControllerOpen(0);

	return true;
}

bool InputManager::Shutdown()
{
	instance.reset(nullptr);

	return true;
}

// clear the state
void InputManager::flush() {
	isKeyDownEvent_ = false;
	isKeyUpEvent_ = false;
	isMouseButtonEvent_ = false;
	isMouseMotionEvent_ = false;

	for (auto i = 0u; i < 3; i++)
		mbState_[i] = false;
}

// update the state with a new event
bool InputManager::update() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return false;

			break;
		case SDL_KEYDOWN:
			onKeyDown(event);
		
			break;
		case SDL_KEYUP:
			onKeyUp(event);
		
			break;
		case SDL_MOUSEMOTION:
			onMouseMotion(event);

			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonChange(event, true);

			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonChange(event, false);

		case SDL_MOUSEWHEEL:
			mouseScrollAmount = event.wheel.y;

			break;
		}
	}

	return true;
}

bool InputManager::keyDownEvent() {
	return isKeyDownEvent_;
}

bool InputManager::keyUpEvent() {
	return isKeyUpEvent_;
}

bool InputManager::isKeyDown(K_Engine_Scancode key) {
	return isKeyDownEvent_ && kbState_[key] == 1;
}

bool InputManager::isKeyDown(K_Engine_Keycode key) {
	return isKeyDownEvent_ && isKeyDown((K_Engine_Scancode)SDL_GetScancodeFromKey(key));
}

bool InputManager::isKeyUp(K_Engine_Scancode key) {
	return isKeyUpEvent_ && kbState_[key] == 0;
}

bool InputManager::isKeyUp(K_Engine_Keycode key) {
	return isKeyUpEvent_ && isKeyUp((K_Engine_Scancode)SDL_GetScancodeFromKey(key));
}

bool InputManager::controllerButtonPressed(SDL_GameController* controller, K_Engine_GameControllerButton button) {
	if(controller != nullptr) return SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)button);

	return false;
}

double InputManager::controllerAxisValue(SDL_GameController* controller, K_Engine_GameControllerAxis axis)
{
	if (controller != nullptr) {
		double value = SDL_GameControllerGetAxis(controller, (SDL_GameControllerAxis)axis);

		switch (axis)
		{
			case SDL_CONTROLLER_AXIS_LEFTX:
			case SDL_CONTROLLER_AXIS_LEFTY:
				if (-deathZoneLeftJoy < value && value < deathZoneLeftJoy) return 0;

				return value;
			break;

			case SDL_CONTROLLER_AXIS_RIGHTX:
			case SDL_CONTROLLER_AXIS_RIGHTY:
				if (-deathZoneRightJoy < value && value < deathZoneRightJoy) return 0;

				return value;
				break;

			case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
				if (-deathZoneLeftTrigger < value && value < deathZoneLeftTrigger) return 0;

				return value;
				break;

			case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
				if (-deathZoneRightTrigger < value && value < deathZoneRightTrigger) return 0;

				return value;
				break;
		}
	}

	return 0;
}

// mouse
bool InputManager::mouseMotionEvent() {
	return isMouseMotionEvent_;
}

bool InputManager::mouseButtonEvent() {
	return isMouseButtonEvent_;
}

std::pair<INT32, INT32>& InputManager::getMousePos() {
	return mousePos_;
}

int InputManager::getMouseButtonState(K_Engine_MouseButton b) {
	return mbState_[(int)b];
}

bool InputManager::getMouseButtonHeld() {
	return isMouseButtonHeldDown_;
}

bool InputManager::getRightMouseButtonPressed() {
	return isRightMousePressed_;
}

bool InputManager::getLeftMouseButtonPressed() {
	return isLeftMousePressed_;
}

float InputManager::mouseScroll()
{
	return mouseScrollAmount;
}

void InputManager::setDeathZones(double deathZoneValue, int axis)
{
	switch (axis)
	{
	case 0:
		deathZoneLeftJoy = deathZoneValue;

		break;
	case 1:
		deathZoneRightJoy = deathZoneValue;

		break;
	case 2:
		deathZoneLeftTrigger = deathZoneValue;

		break;
	case 3:
		deathZoneRightTrigger = deathZoneValue;

		break;
	}
}

void InputManager::onKeyDown(const SDL_Event& e) {
	isKeyDownEvent_ = true;
}

void InputManager::onKeyUp(const SDL_Event& e) {
	isKeyUpEvent_ = true;
}

void InputManager::onMouseMotion(const SDL_Event & event) {
	isMouseMotionEvent_ = true;
	mousePos_.first = event.motion.x;
	mousePos_.second = event.motion.y;
}

void InputManager::onMouseButtonChange(const SDL_Event & event, bool isDown) {
	isMouseButtonEvent_ = true;
	isMouseButtonHeldDown_ = isDown;
	switch (event.button.button) {
	case SDL_BUTTON_LEFT:
		mbState_[(int)K_Engine_MouseButton::LEFT] = isDown;
		isLeftMousePressed_ = isDown;
		break;
	case SDL_BUTTON_MIDDLE:
		mbState_[(int)K_Engine_MouseButton::MIDDLE] = isDown;
		break;
	case SDL_BUTTON_RIGHT:
		mbState_[(int)K_Engine_MouseButton::RIGHT] = isDown;
		isRightMousePressed_ = isDown;
		break;
	default:
		break;
	}
}
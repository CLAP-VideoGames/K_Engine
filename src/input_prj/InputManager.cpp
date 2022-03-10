#include "InputManager.h"

#include <iostream>

#include <SDL.h>
#include <SDL_syswm.h>

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
		case SDL_KEYDOWN:
			onKeyDown(event);
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				return false;
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
			break;
		default:
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

bool InputManager::isKeyDown(SDL_Scancode key) {
	return keyDownEvent() && kbState_[key] == 1;
}

bool InputManager::isKeyDown(SDL_Keycode key) {
	return isKeyDown(SDL_GetScancodeFromKey(key));
}

bool InputManager::isKeyUp(SDL_Scancode key) {
	return keyUpEvent() && kbState_[key] == 0;
}

bool InputManager::isKeyUp(SDL_Keycode key) {
	return isKeyUp(SDL_GetScancodeFromKey(key));
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

int InputManager::getMouseButtonState(MouseButtons b) {
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

void InputManager::onKeyDown(const SDL_Event&) {
	isKeyDownEvent_ = true;
}

void InputManager::onKeyUp(const SDL_Event&) {
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
		mbState_[(int)MouseButtons::LEFT] = isDown;
		isLeftMousePressed_ = isDown;
		break;
	case SDL_BUTTON_MIDDLE:
		mbState_[(int)MouseButtons::MIDDLE] = isDown;
		break;
	case SDL_BUTTON_RIGHT:
		mbState_[(int)MouseButtons::RIGHT] = isDown;
		isRightMousePressed_ = isDown;
		break;
	default:
		break;
	}
}
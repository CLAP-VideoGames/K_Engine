#pragma once

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <array>
#include <memory>

class SDL_Event;

class InputManager {
public:
	enum MOUSEBUTTON : uint8_t {
		LEFT = 0, MIDDLE = 1, RIGHT = 2
	};

	InputManager();
	~InputManager();

	static InputManager* getInstance();

	static bool Init();
	static bool Shutdown();

	void clearState();
	void update(SDL_Event& event);

	bool keyDownEvent();
	bool keyUpEvent();
	bool isKeyDown(SDL_Scancode key);
	bool isKeyDown(SDL_Keycode key);
	bool isKeyUp(SDL_Scancode key);
	bool isKeyUp(SDL_Keycode key);
	bool mouseMotionEvent();
	bool mouseButtonEvent();
	std::pair<INT32, INT32>& getMousePos();
	int getMouseButtonState(MOUSEBUTTON b);
	bool getMouseButtonHeld();
	bool getRightMouseButtonPressed();
	bool getLeftMouseButtonPressed();

	

private:
	static std::unique_ptr<InputManager> instance;

	bool isKeyUpEvent_;
	bool isKeyDownEvent_;
	bool isMouseMotionEvent_;
	bool isMouseButtonEvent_;
	//Esto es para ver que se sigue pulsando
	bool isMouseButtonHeldDown_;
	bool isRightMousePressed_;
	bool isLeftMousePressed_;
	std::pair<Sint32, Sint32> mousePos_;
	std::array<bool, 3> mbState_;
	const Uint8* kbState_;

	void onKeyDown(const SDL_Event& e);
	void onKeyUp(const SDL_Event& e);
	void onMouseMotion(const SDL_Event& event);
	void onMouseButtonChange(const SDL_Event& event, bool isDown);
};

#endif //INPUTMANAGER_H
#pragma once
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <array>
#include <memory>

#include <SDL_scancode.h>
#include <SDL_keycode.h>

union SDL_Event;

enum class MouseButtons : uint8_t {
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputManager {
public:
	InputManager();
	~InputManager();

	static InputManager* GetInstance();

	static bool Init();
	static bool Shutdown();

	void flush();
	bool update();

	bool keyDownEvent();
	bool keyUpEvent();

	bool isKeyDown(SDL_Scancode key);
	bool isKeyDown(SDL_Keycode key);

	bool isKeyUp(SDL_Scancode key);
	bool isKeyUp(SDL_Keycode key);

	bool mouseMotionEvent();
	bool mouseButtonEvent();

	std::pair<int, int>& getMousePos();

	int getMouseButtonState(MouseButtons b);
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
	
	std::pair<int, int> mousePos_;
	std::array<bool, 3> mbState_;
	
	const Uint8* kbState_;

	void onKeyDown(const SDL_Event& e);
	void onKeyUp(const SDL_Event& e);
	
	void onMouseMotion(const SDL_Event& event);
	void onMouseButtonChange(const SDL_Event& event, bool isDown);
};
#endif //INPUTMANAGER_H
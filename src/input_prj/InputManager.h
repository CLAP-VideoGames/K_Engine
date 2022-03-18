#pragma once
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <array>
#include <memory>

#include <SDL_scancode.h>
#include <SDL_keycode.h>
#include <SDL_gamecontroller.h>

union SDL_Event;

class InputManager {
public:
	//Enum with the buttons
	enum MouseButtons : uint8_t {
		LEFT = 0,
		MIDDLE = 1,
		RIGHT = 2
	};


	InputManager();
	~InputManager();

	//Instance of our Singleton
	static InputManager* GetInstance();

	//Starts the singleton
	static bool Init();

	//Deletes everything we need to delete
	static bool Shutdown();

	//Clears the state
	void flush();

	//Detects input
	bool update();

	bool keyDownEvent();
	bool keyUpEvent();

	//Scancode is the physical position of the key
	bool isKeyDown(SDL_Scancode key);

	//KeyCode is the actual key, no matter where it is in the keyboard
	bool isKeyDown(SDL_Keycode key);

	//Scancode is the physical position of the key
	bool isKeyUp(SDL_Scancode key);

	//KeyCode is the actual key, no matter where it is in the keyboard
	bool isKeyUp(SDL_Keycode key);

	//Return if a button is pressed (parameter button)
	bool controllerButtonPressed(SDL_GameController* controller, SDL_GameControllerButton button);

	//Detects when the mouse is moving
	bool mouseMotionEvent();

	//Detects when a mouse button is clicked
	bool mouseButtonEvent();

	//The actual position of the mouse
	std::pair<int, int>& getMousePos();

	//return 1, 2, or 3 (left, center and right, repectively)
	int getMouseButtonState(MouseButtons b);

	//Any mouse button held
	bool getMouseButtonHeld();

	//Right button pressed
	bool getRightMouseButtonPressed();

	//Left button pressed
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

	//The key that is being pressed
	const Uint8* kbState_;

	//this method is called when a keyIsDown and it set the boolean
	//keyDown event to true
	void onKeyDown(const SDL_Event& e);

	//Same as the method from above but with key up
	void onKeyUp(const SDL_Event& e);
	
	//Sets the mouse motion boolean true and changes the paor of the
	//Mouse position
	void onMouseMotion(const SDL_Event& event);

	//Change the booleans of the vector mBState to true or false
	//if they have been clicked
	void onMouseButtonChange(const SDL_Event& event, bool isDown);
};
#endif //INPUTMANAGER_H
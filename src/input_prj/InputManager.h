#pragma once
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <array>
#include <memory>

#include <input_prj/K_Engine_Keys.h>

#define DEATHZONEMAX 32000
#define DEATHZONEMIN 0

union SDL_Event;
typedef struct _SDL_GameController SDL_GameController;

namespace K_Engine {
	class  __declspec(dllexport) InputManager {
	public:
		InputManager();
		~InputManager();

		//Instance of our Singleton
		static InputManager* GetInstance();

		//Starts the singleton
		static bool Init();

		//Deletes everything we need to delete
		static bool Shutdown();

		//Detects input
		bool update();

		//Clears the state
		void flush();

		// default setup
		void setupInput();

		//Scancode is the physical position of the key
		bool isKeyDown(K_Engine_Scancode key);
		//KeyCode is the actual key, no matter where it is in the keyboard
		bool isKeyDown(K_Engine_Keycode key);

		//Scancode is the physical position of the key
		bool isKeyUp(K_Engine_Scancode key);
		//KeyCode is the actual key, no matter where it is in the keyboard
		bool isKeyUp(K_Engine_Keycode key);

		//Return if a button is pressed (parameter button)
		bool controllerButtonPressed(K_Engine_GameControllerButton button);

		/// <summary>
		/// This method returns the value of the given axis(this can be a trigger or a joystick)
		/// If there is no controller it returns 0
		/// </summary>
		/// <param name="controller"></param>
		/// <param name="axis"></param>
		/// <returns></returns>
		double controllerAxisValue(K_Engine_GameControllerAxis axis);

		//Detects when the mouse is moving
		bool mouseMotionEvent();
		//Detects when a mouse button is clicked
		bool mouseButtonEvent();

		//The actual position of the mouse
		std::pair<int, int> getMousePos();

		//return 1, 2, or 3 (left, center and right, repectively)
		int getMouseButtonState(K_Engine_MouseButton b);

		//Any mouse button held
		bool getMouseButtonHeld();
		//Right button pressed
		bool getRightMouseButtonPressed();
		//Left button pressed
		bool getLeftMouseButtonPressed();

		//Return the amount scroll of the mouse
		float mouseScroll();

		/// <summary>
		/// Default value for everyDeathZone is 3000, maximum is 32000
		/// The first parameter is the new value of the deathZone 
		/// And the second is the axis being 0 = LeftJoyStick 1 = RightJoyStick 2 = LeftTrigger 3 = RightTrigger
		/// </summary>
		/// <param name="deathZoneValue"></param>
		/// <param name="axis"></param>
		void setDeathZones(double deathZoneValue, int axis);

	private:
		static std::unique_ptr<InputManager> instance;

		bool isKeyUpEvent_ = false;
		bool isKeyDownEvent_ = false;

		bool isMouseMotionEvent_ = false;
		bool isMouseButtonEvent_ = false;

		//Esto es para ver que se sigue pulsando
		bool isMouseButtonHeldDown_ = false;
		bool isRightMousePressed_ = false;
		bool isLeftMousePressed_ = false;

		//Editable deathZone for our joySticks
		float deathZoneLeftJoy = 3000;
		float deathZoneRightJoy = 3000;

		//Editable deathZone for our Trigger
		float deathZoneRightTrigger = 3000;
		float deathZoneLeftTrigger = 3000;

		//Information of the mouse
		std::pair<int, int> mousePos_;
		std::array<bool, 3> mbState_;
		float mouseScrollAmount;

		//For xbox controller
		SDL_GameController* controller;

		//The key that is being pressed
		const Uint8* kbState_;

		void initInput();

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

		bool keyDownEvent();
		bool keyUpEvent();
	};
}
#endif //INPUTMANAGER_H
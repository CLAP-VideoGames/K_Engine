#pragma once

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <memory>

class InputManager {
public:
	InputManager();
	~InputManager();

	static InputManager* getInstance();

	static bool Init();
	static bool Shutdown();

	

private:
	static std::unique_ptr<InputManager> instance;
};


#endif //INPUTMANAGER_H
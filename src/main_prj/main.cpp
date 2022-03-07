#include <stdio.h>
#include <iostream>

#include <OgreLogManager.h>
#include <btBulletDynamicsCommon.h>

#include <SDL_timer.h>
#include <SDL.h>

#include <physics_prj/PhysicsManager.h>
#include <render_prj/RenderManager.h>
#include <sound_prj/SoundExample.h>
#include <ui_prj/UIManager.h>

#define DELTA_TIME 33

bool pollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			std::cout << "exit\n";
			return false;
			break;
		default:
			break;
		}
	}
	return true;
}

int main(int argc, char** argv) {
	try {
		RenderManager* renderMan = RenderManager::getInstance();
		renderMan->init("K_Engine");
		//UI MUST BE AFTER RENDER
		UIManager* uiMan = UIManager::getInstance();
		uiMan->init();

		renderMan->exampleScene();

		PhysicsManager* physicsMan = PhysicsManager::getInstance();
		physicsMan->init(10, 20, { 0, -9.8, 0});
		physicsMan->exampleObjects();
		
		SoundExample* sExample = new SoundExample();

		//sExample->playWAV("./assets/sounds/clap.wav");
		//sExample->playMP3("./assets/sounds/clapV2.ogg");


		bool run = true; // time --> miliseconds
		unsigned int accFrameTime = 0, currTime = SDL_GetTicks();
		int cycles = 10000;
		while (run) {
			unsigned int frame = SDL_GetTicks() - currTime;
			currTime += frame;

			accFrameTime += frame;
			while (accFrameTime >= DELTA_TIME) {
				// get input here (clear and check same time)
				// TEMPORAL
				run = pollEvents();
				//physicsMan->Update();
				accFrameTime -= DELTA_TIME;
			}

			renderMan->render();
		}

		renderMan->shutdown();
		physicsMan->shutdown();
		uiMan->shutdown();
	}
	catch (Ogre::Exception& e) {

		Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
	}

	return 0;
}
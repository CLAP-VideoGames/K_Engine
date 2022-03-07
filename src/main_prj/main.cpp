#include <stdio.h>
#include <iostream>

#include <OgreLogManager.h>
#include <btBulletDynamicsCommon.h>

#include <SDL_timer.h>
#include <SDL.h>

#include <physics_prj/PhysicsManager.h>
#include <render_prj/RenderManager.h>
#include <sound_prj/SoundExample.h>

#define DELTA_TIME 33

int main(int argc, char** argv) {
	try {
		RenderManager* renderMan = RenderManager::getInstance();
		renderMan->init("K_Engine");
		renderMan->exampleScene();

		PhysicsManager* physicsMan = PhysicsManager::getInstance();
		physicsMan->init(10, 20, { 0, -9.8, 0});
		physicsMan->exampleObjects();
		
		SoundExample* sExample = new SoundExample();


		//sExample->playWAV("./assets/sounds/clap.wav");
		//sExample->playMP3("./assets/sounds/clapV2.ogg");
		//sExample->playMP3("./assets/sounds/snare.mp3");


		bool run = true; // time --> miliseconds
		unsigned int accFrameTime = 0, currTime = SDL_GetTicks();
		int cycles = 100;
		while (run) {
			unsigned int frame = SDL_GetTicks() - currTime;
			currTime += frame;

			accFrameTime += frame;
			while (accFrameTime >= DELTA_TIME) {
				// get input here (clear and check same time)
				physicsMan->update();
				accFrameTime -= DELTA_TIME;
			}

			renderMan->render();

			// TEMPORAL SOLUTION
			cycles--;
			if (cycles < 0)
				run = false;
		}

		renderMan->shutdown();
		delete physicsMan;
	}
	catch (Ogre::Exception& e) {

		Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
	}

	return 0;
}


#include <stdio.h>
#include <iostream>

#include <OgreLogManager.h>
#include <physics_prj/PhysicsExample.h>
#include <render_prj/RenderExample.h>
#include <sound_prj/SoundExample.h>

int main(int argc, char** argv) {
	try {
		RenderExample* rExample = new RenderExample();
		PhysicsExample* example = new PhysicsExample({ 0, -9.8, 0 });
		SoundExample* sExample = new SoundExample();

		//sExample->playWAV("./assets/sounds/clap.wav");
		sExample->playMP3("./assets/sounds/snare.mp3");

		int i = 0;
		int limit = 50;
		while (i < limit) {
			example->Update();
			rExample->render();
			i++;
		}

		delete example;
		delete rExample;
	}
	catch (Ogre::Exception& e) {

		Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
	}

	return 0;
}


#include <stdio.h>
#include <iostream>

#include <physics_prj/PhysicsExample.h>
#include <render_prj/RenderExample.h>
#include <OgreLogManager.h>
int main(int argc, char** argv) {
	try {
		RenderExample* rExample = new RenderExample();

		rExample->render();

		/*PhysicsExample* example = new PhysicsExample({ 0, -9.8, 0 });
		example->Update();

		delete example;*/

		//delete rExample;
	}
	catch (Ogre::Exception& e) {

		Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
	}

	return 0;
}
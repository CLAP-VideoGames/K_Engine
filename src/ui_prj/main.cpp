#include <stdio.h>

#include "HelloWorld.h"
#include "CEGUI/CEGUI.h"

using namespace CEGUI;


int main(int argc, char** argv) {
	try {
		/*OgreRenderer& myRenderer =
			OgreRenderer::bootstrapSystem();*/

		HelloWorldSample* sample = new HelloWorldSample();
		sample->initialise(&System::getSingleton().getDefaultGUIContext());

		delete sample;
	}
	catch (int m) {
	}

	return 0;
}
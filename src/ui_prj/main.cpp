#include <stdio.h>

#include "HelloWorld.h"

int main(int argc, char** argv) {
	try {
		HelloWorldSample* sample = new HelloWorldSample();

		sample->initialise();

		delete sample;
	}
	catch (int m) {
	}

	return 0;
}


#include <stdio.h>
#include <physics_prj/PhysicsExample.h>

int main(int argc, char** argv) {
	
	PhysicsExample* example = new PhysicsExample({0, -9.8, 0});

	example->Update();

	delete example;
	
	return 0;
}
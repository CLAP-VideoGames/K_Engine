

#include <stdio.h>
#include <iostream>
#include <physics_prj/PhysicsExample.h>
#include <render_prj/RenderExample.h>

int main(int argc, char** argv) {
	try {
		RenderExample* rExample = new RenderExample();

		PhysicsExample* example = new PhysicsExample({ 0, -9.8, 0 });

		example->Update();

		delete example;
		delete rExample;
	}
	catch (Exception e) {
		std::cout << e.what();
	}

	return 0;
}
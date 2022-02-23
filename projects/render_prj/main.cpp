#include <iostream>
#include <fstream>

#include <Ogre.h>
#include <SDL.h>

namespace Ogre { 
	class Root;
	class RenderWindow;
	class Camera;
	class SceneManager;
	class Viewport;
	class SceneNode;
	class FileSystemLayer;
	class Log;
	class LogManager;
}

void main()
{
	std::fstream myfile;
	try {
		myfile.open("test.txt");
		std::cout << "anda";
	}
	catch (std::string e) {
		std::cout << "vaya";
	}
		
	myfile.close();
}
#pragma once
#include <stack>

class Scene;

class SceneManager
{
public:
	//Default constructor
	SceneManager();

	//Clears the scene stack
	~SceneManager();

	//Allows the user to pop the scenes stack
	void popScene();

	//Allows the user to push a new scene into the stack
	void pushScene(Scene* newS);

	/// <summary>
	/// Pops the actual scene and pushes the new scene
	/// </summary>
	/// <param name="newS"></param>
	void changeScene(Scene* newS);

	/// <summary>
	/// called once per frame, it calls the actual scene update
	/// </summary>
	void updateScene();

	/// <summary>
	/// returns the top of the scene stack
	/// </summary>
	/// <returns></returns>
	Scene* actualSecne();
private:

	std::stack<Scene*> scenes;
};


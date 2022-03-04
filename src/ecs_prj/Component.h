#pragma once
#include <string>

using namespace std;
/// <summary>
/// You have to specify the id of the component with a string
/// The engine will throw an exception otherwise
/// </summary>
class Component
{
public:
	Component(string id);
	~Component();

	//update is called every frame of the game
	virtual void update(){};

	//start is called once the game starts
	virtual void start(){};

	//awake is called every time the component is activated
	virtual void awake(int bobo){};

	string getId() { return id; }

	void setActive(bool a) { active = a; }

protected:
	std::string id = "unknown";
	bool active;

private:

};
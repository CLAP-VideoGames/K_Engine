#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H


class ComponentFactory
{
public:
	ComponentFactory() = default;
	~ComponentFactory() {};

	static ComponentFactory GetInstance();

	static bool Init();

private:

};

#endif
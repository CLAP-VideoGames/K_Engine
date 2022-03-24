#include "UIComponent.h"
#include "UIManager.h"

#include <iostream>
#include <string>

#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>


UIComponent::UIComponent(CEGUI::WindowManager* winMngr, CEGUI::DefaultWindow* mRoot, std::string& schemeName, Vector2 pos_, Vector2 size_, std::string name_): pos(pos_), size(size_), name(name_)
{}

UIComponent::~UIComponent()
{
	uiWindow->destroy();
}

Vector2 UIComponent::normalizeVector2(const Vector2& v)
{
	float x = std::pow(v.first, 2);
	float y = std::pow(v.second, 2);;
	float sqr = std::sqrt(x + y);
	Vector2 vec;
	vec.first = v.first / sqr;
	vec.second = v.second / sqr;

	return vec;
}

void UIComponent::setPosition(const Vector2& p)
{
	pos = p;
	CEGUI::UDim x(pos.first, 0);
	CEGUI::UDim y(pos.second, 0);
	CEGUI::UVector2 pU(x, y);

	uiWindow->setPosition(pU);
}

void UIComponent::setSize(const Vector2& s)
{
	size = s;
	CEGUI::UDim x(size.first, 0);
	CEGUI::UDim y(size.second, 0);
	CEGUI::USize sU(x, y);
	uiWindow->setSize(sU);
}

void UIComponent::setName(const std::string& n)
{
	name = n;
	uiWindow->setName(name);
}

void UIComponent::setProperty(const std::string nameProp, const std::string value)
{
	try
	{
		uiWindow->setProperty(nameProp, value);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void UIComponent::activate(bool state) {
	if (state)
		uiWindow->activate();
	else
		uiWindow->deactivate();
}

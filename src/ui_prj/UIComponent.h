#pragma once
#ifndef UICOMPONENT_H
#define UICOMPONENT_H
#include <iostream>

namespace CEGUI {
	class WindowManager;
	class DefaultWindow;
	class Window;
	class SubscriberSlot;
}

using Vector2 = std::pair<float, float>;

class UIComponent {

public:
	virtual ~UIComponent();
	// Setters
	void setPosition(const Vector2& p);
	void setSize(const Vector2& s);
	void setName(const std::string& n);
	void setProperty(const std::string nameProp, const std::string value);
	void activate(bool state);

protected:
	Vector2 pos;
	Vector2 size;
	std::string name;
	std::string type;
	CEGUI::Window* uiWindow = nullptr;

	UIComponent(CEGUI::WindowManager* winMngr, CEGUI::DefaultWindow* mRoot, std::string& schemeName, Vector2 pos_, Vector2 size_, std::string name_);
/// <summary>
/// Normaliza el vector size del objeto para usar 
/// el posicionamiento
/// </summary>
	Vector2 normalizeVector2(const Vector2& v);
};

#endif

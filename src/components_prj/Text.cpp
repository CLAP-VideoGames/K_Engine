#include "Text.h"

#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UIText.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

#include <utils_prj/K_Map.h>

namespace K_Engine {
	//Required
	std::string Text::name = "Text";

	std::string K_Engine::Text::GetId() {
		return name;
	}

	Text::Text() : Component() {}

	K_Engine::Text::Text(Entity* e) : Component(e) {}

	Text::Text(Entity* e, std::string overlayName, std::string fontName, int fontSize, std::string text, Vector3 textColor) : Component(e) {
		overlayName_ = overlayName;
		fontName_ = fontName;
		text_ = text;

		fontSize_ = fontSize;
		textColor_ = textColor;
	}

	K_Engine::Text::~Text() = default;

	void Text::init(K_Map* information)
	{
		overlayName_ = information->value("overlayName");
		fontName_ = information->value("fontName");
		text_ = information->value("text");

		fontSize_ = information->valueToNumber("fontSize");
		textColor_ = *(information->valueToVector3("textColor"));
	}

	void K_Engine::Text::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		uitext_ = UIManager::GetInstance()->addWidget<UIText>(overlayName_, fontName_, fontSize_, text_, textColor_);
	}

	void Text::update(int frameTime)
	{
		syncData();
	}

	void Text::changeText(std::string newText)
	{
		text_ = newText;
		if (uitext_ != nullptr) uitext_->setText(newText);
	}

	void Text::syncData()
	{
		// Position syncing
		uitext_->setPosition(transformRf_->getPosition().x, transformRf_->getPosition().y);
		// Size syncing
		uitext_->setSize(uitext_->getSize().first * transformRf_->getScale().x, uitext_->getSize().second * transformRf_->getScale().y);
		// ZOrder syncing
		uitext_->setRenderOrder((int)transformRf_->getPosition().z);
	}
}
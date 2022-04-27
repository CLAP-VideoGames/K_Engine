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

	void Text::init(K_Map* information)
	{
		overlayName_ = information->value("overlayName");
		text_ = information->value("text");
		offsetX = 0;
		offsetY = 0;
	}

	Text::Text() : Component() {}

	K_Engine::Text::Text(Entity* e) : Component(e) {}

	Text::Text(Entity* e, std::string overlayName, std::string text) : Component(e) {
		overlayName_ = overlayName;
		text_ = text;
		offsetX = 0;
		offsetY = 0;
	}

	K_Engine::Text::~Text() = default;

	void K_Engine::Text::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		uitext_ = UIManager::GetInstance()->addWidget<UIText>(overlayName_, "MyFont", text_);
	}

	void Text::update(int frameTime)
	{
		//Position syncing
		Vector3 pos = transformRf_->getPosition();
		uitext_->setPosition(transformRf_->getPosition().x+ offsetX, transformRf_->getPosition().y + offsetY);

		//Scale syincing
		uitext_->setSize(uitext_->getSize().first * transformRf_->getScale().x, uitext_->getSize().second * transformRf_->getScale().y);

		//ZOrder syncing
		uitext_->setRenderOrder(transformRf_->getPosition().z);
	}

	void Text::changeText(std::string newText)
	{
		text_ = newText;
		if (uitext_ != nullptr) uitext_->setText(newText);
	}

	void Text::changeTextPosition(int x, int y)
	{
		offsetY = y;
		offsetX = x;
	}
}
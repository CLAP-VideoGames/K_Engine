#include "Text.h"

#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UiText.h>

#include <utils_prj/Vector3.h>

namespace K_Engine {
	//Required
	std::string Text::name = "Text";

	K_Engine::Text::Text(Entity* e) : Component("Text", e)
	{
		name = id;
	}

	Text::Text(Entity* e, std::string overlayName, std::string text) : Component("Text", e)
	{
		name = id;
		overlayName_ = overlayName;
		text_ = text;
	}

	K_Engine::Text::~Text() = default;

	std::string K_Engine::Text::GetId()
	{
		return name;
	}

	void K_Engine::Text::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		uitext_ = UIManager::GetInstance()->addText(overlayName_, text_);
	}
	void Text::update(int frameTime)
	{
		//Position syncing
		Vector3 pos = transformRf_->getPosition();
		uitext_->setPosition(transformRf_->getPosition().x, transformRf_->getPosition().y);

		//Scale syincing
		uitext_->setSize(uitext_->getSize().first * transformRf_->getScale().x, uitext_->getSize().second * transformRf_->getScale().y);

		//ZOrder syncing
		uitext_->setRenderOrder(transformRf_->getPosition().z);
	}
}
#include "Image.h"

#include <ecs_prj/Entity.h>

#include <components_prj/Transform.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UiImage.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

namespace K_Engine {
	//Required
	std::string Image::name = "Image";

	Image::Image() : Component()
	{
	}

	K_Engine::Image::Image(Entity* e) : Component( e)
	{
	}

	Image::Image(Entity* e, std::string overlayName, std::string imageName) : Component( e){
		overlayName_ = overlayName;
		imageName_ = imageName;
	}

	K_Engine::Image::~Image() = default;

	std::string K_Engine::Image::GetId()
	{
		return name;
	}

	void K_Engine::Image::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		image_ = UIManager::GetInstance()->addImage(overlayName_, imageName_);
	}

	void Image::update(int frameTime)
	{
		//Position syncing
		Vector3 pos = transformRf_->getPosition();
		image_->setPosition(transformRf_->getPosition().x, transformRf_->getPosition().y);

		//Scale syincing
		image_->setSize(image_->getSize().first * transformRf_->getScale().x, image_->getSize().second * transformRf_->getScale().y);

		//ZOrder syncing
		image_->setRenderOrder(transformRf_->getPosition().z);
	}
}
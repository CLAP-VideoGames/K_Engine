#include "Image.h"

#include <ecs_prj/Entity.h>

#include <components_prj/Transform.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UIImage.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

#include <utils_prj/K_Map.h>

namespace K_Engine {
	//Required
	std::string Image::name = "Image";

	std::string Image::GetId() {
		return name;
	}

	Image::Image() : Component() {}

	Image::Image(Entity* e) : Component(e) {}

	Image::Image(Entity* e, std::string overlayName, std::string imageName) : Component(e) {
		overlayName_ = overlayName;
		imageName_ = imageName;
	}

	Image::~Image() = default;

	void Image::init(K_Map* information)
	{
		overlayName_ = information->value("overlayName");
		imageName_ = information->value("imageName");
	}

	void Image::onEnable()
	{
		if (image_ != nullptr)
			image_->show();
	}

	void Image::onDisable()
	{
		image_->hide();
	}

	void Image::start()
	{
		transformRf_ = entity->getComponent<Transform>();

		image_ = UIManager::GetInstance()->addWidget<UIImage>(overlayName_, imageName_);
		syncData();
	}

	void Image::update(int frameTime) {
		syncData();
	}

	void Image::syncData()
	{
		// Position syncing
		image_->setPosition(transformRf_->getPosition().x, transformRf_->getPosition().y);
		// Size syncing
		image_->setSize(image_->getSize().first * transformRf_->getScale().x, image_->getSize().second * transformRf_->getScale().y);
		// ZOrder syncing
		image_->setRenderOrder((int)transformRf_->getPosition().z);
	}
}
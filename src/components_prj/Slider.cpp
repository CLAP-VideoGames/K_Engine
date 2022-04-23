#include <components_prj/Slider.h>

#include <components_prj/Transform.h>

#include <ecs_prj/Entity.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UiSlider.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

namespace K_Engine {
	//Required
	std::string Slider::name = "Slider";

	Slider::Slider() : Component() {
	}

	K_Engine::Slider::Slider(Entity* e) : Component(e) {
	}

	Slider::Slider(Entity* e, std::string overlayName, std::string imageName, int x, int leftLimit, int rightLimit) : Component(e)
	{
		overlayName_ = overlayName;
		imageName_ = imageName;
		x_ = x;
		leftLimit_ = leftLimit;
		rightLimit_ = rightLimit;
	}

	K_Engine::Slider::~Slider() = default;

	std::string K_Engine::Slider::GetId()
	{
		return name;
	}

	void K_Engine::Slider::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		slider_ = UIManager::GetInstance()->addSlider(overlayName_, imageName_, x_, leftLimit_, rightLimit_);
	}
	void Slider::update(int frameTime)
	{
		//Position syncing
		//Transform actualization if there was a change in position
		//if (scrollBar_->getNeedsSync()) {
		//	transformRf_->setPosition(transformRf_->getPosition().x, scrollBar_->getPosition().second, transformRf_->getPosition().z);
		//	scrollBar_->setNeedsSync(false);
		//}

		//////Element actualization
		//scrollBar_->updatePosition(transformRf_->getPosition());

		//Scale syincing
		/*scrollBar_->setSize(scrollBar_->getSize().first * transformRf_->getScale().x, scrollBar_->getSize().second * transformRf_->getScale().y);*/

		//ZOrder syncing
		/*scrollBar_->setRenderOrder(transformRf_->getPosition().z);*/
	}
}
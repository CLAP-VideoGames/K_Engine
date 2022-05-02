#include <components_prj/Slider.h>

#include <components_prj/Transform.h>
#include <components_prj/ProgressBar.h>
#include <components_prj/Image.h>

#include <ecs_prj/Entity.h>

#include <ui_prj/UIManager.h>
#include <ui_prj/UISlider.h>
#include <ui_prj/Rectangle.h>

#include <utils_prj/Vector3.h>
#include <utils_prj/checkML.h>

#include <input_prj/InputManager.h>
#include <utils_prj/K_Map.h>

#include <render_prj/RenderManager.h>

#include <sound_prj/AudioManager.h>

namespace K_Engine {
	//Required
	std::string Slider::name = "Slider";

	std::string K_Engine::Slider::GetId() {
		return name;
	}

	Slider::Slider() : Component() {}

	K_Engine::Slider::Slider(Entity* e) : Component(e) {}

	Slider::Slider(Entity* e, std::string overlayName, std::string imageName, float width, float height) : Component(e) {
		overlayName_ = overlayName;
		imageName_ = imageName;
		width_ = width;
		height_ = height;

		inputArea = new Rectangle();

		inputMan = K_Engine::InputManager::GetInstance();

		pressed_ = false;
		controllerChangingValue = false;
	}

	K_Engine::Slider::~Slider() {
		delete inputArea; inputArea = nullptr;
	}

	void Slider::init(K_Map* information)
	{
		overlayName_ = information->value("overlayName");
		imageName_ = information->value("imageName");
		width_ = information->valueToNumber("width");
		height_ = information->valueToNumber("height");

		keyCallback_ = information->value("onSliderClick");
		onSliderClick = information->valueToFunction(keyCallback_, 1.0f);

		inputArea = new Rectangle();

		inputMan = K_Engine::InputManager::GetInstance();

		pressed_ = false;
		controllerChangingValue = false;
	}

	void Slider::onEnable()
	{
		if (slider_ != nullptr)
			slider_->show();
	}

	void Slider::onDisable()
	{
		slider_->hide();
	}

	void K_Engine::Slider::start()
	{
		transformRf_ = entity->getComponent<Transform>();
		x_ = transformRf_->getPosition().x;
		rightLimit_ = x_ + width_;
		y_ = transformRf_->getPosition().y;

		initialPosition = AudioManager::GetInstance()->getMasterVolume();

		slider_ = UIManager::GetInstance()->addWidget<UISlider>(overlayName_, imageName_, x_, y_, width_, height_, initialPosition);

		progressBar_ = entity->addComponent<ProgressBar>(overlayName_ + " progress", "DefaultProgressBar", width_, height_);
		progressBar_->setCustomRenderOrder(5);
		progressBar_->setProgress(slider_->getRelativePos());

		background_ = entity->addComponent<Image>(overlayName_ + " background", "GreenDefaultProgressBar", width_, height_);
		background_->setDimensions(width_, height_);
		background_->setInteractive(true);
	}

	void Slider::update(int frameTime)
	{
		//Setup the input area rectangle
		inputArea->x = slider_->getPosition().first * RenderManager::GetInstance()->windowWidth();
		inputArea->y = slider_->getPosition().second * RenderManager::GetInstance()->windowHeight();
		inputArea->w = slider_->getSize().first * RenderManager::GetInstance()->windowWidth();
		inputArea->h = slider_->getSize().second * RenderManager::GetInstance()->windowHeight();

		Point pointer;
		auto pointPos = inputMan->getMousePos();
		pointer.x = pointPos.first;
		pointer.y = pointPos.second;

		if (inputMan->getLeftMouseButtonPressed())
		{
			if (PointInRect(&pointer, inputArea)) {
				pressed_ = true;
			}
		}
		else
			pressed_ = false;

		if (pressed_) {
			auto x = slider_->getPosition().first;
			if (x >= x_ && x <= rightLimit_) {
				if (pointer.x >= x_ * RenderManager::GetInstance()->windowWidth() && pointer.x <= (rightLimit_ - slider_->getSize().first) * RenderManager::GetInstance()->windowWidth()) {
					slider_->setLeft((float)pointer.x / (float)RenderManager::GetInstance()->windowWidth());
					progressBar_->setProgress(slider_->getRelativePos());
					if (onSliderClick != nullptr)
						onSliderClick(keyCallback_, slider_->getRelativePos() / 100.0f);
				}
			}
		}

		if (background_->getIsFocus()) {
			if (controllerChangingValue) {
				//Comprobamos si hay que mover el slider o terminar de cambiarlo
				if (inputMan->controllerButtonPressed(CONTROLLER_BUTTON_A) || inputMan->controllerButtonPressed(CONTROLLER_BUTTON_B)) {
					controllerChangingValue = false;
					//Cambiamos de vuelta el material
				}
				else {
					if (inputMan->controllerAxisValue(CONTROLLER_AXIS_LEFTX) > 0.5 ||
						inputMan->controllerButtonPressed(CONTROLLER_BUTTON_DPAD_RIGHT)) {
						if (slider_->getPosition().first + 5 <= rightLimit_ - slider_->getSize().first) {
							slider_->setLeft(slider_->getPosition().first + 5);
							progressBar_->setProgress(slider_->getRelativePos());
							if (onSliderClick != nullptr)
								onSliderClick(keyCallback_, slider_->getRelativePos() / 100.0f);
						}
						else {
							if (slider_->getPosition().first != rightLimit_ - slider_->getSize().first) {
								slider_->setLeft(rightLimit_ - slider_->getSize().first);
								progressBar_->setProgress(slider_->getRelativePos());
								if (onSliderClick != nullptr)
									onSliderClick(keyCallback_, slider_->getRelativePos() / 100.0f);
							}
						}

					}
					else if (inputMan->controllerAxisValue(CONTROLLER_AXIS_LEFTX) < -0.5 ||
						inputMan->controllerButtonPressed(CONTROLLER_BUTTON_DPAD_LEFT)) {
						if (slider_->getPosition().first - 5 >= x_) {
							slider_->setLeft(slider_->getPosition().first - 5);
							progressBar_->setProgress(slider_->getRelativePos());
							if (onSliderClick != nullptr)
								onSliderClick(keyCallback_, slider_->getRelativePos() / 100.0f);
						}
						else {
							if (slider_->getPosition().first != x_) {
								slider_->setLeft(x_);
								progressBar_->setProgress(slider_->getRelativePos());
								if (onSliderClick != nullptr)
									onSliderClick(keyCallback_, slider_->getRelativePos() / 100.0f);
							}
						}
					}
				}
			}
			else {
				//Comprobamos si se quiere empezar a cambiar el valor
				if (inputMan->controllerButtonPressed(CONTROLLER_BUTTON_A)) {
					controllerChangingValue = true;
					//Cambiamos el material del slider
				}
			}
		}

		//Position syncing
		slider_->setLeft(transformRf_->getPosition().x + (slider_->getPosition().first - x_));
		slider_->setTop(transformRf_->getPosition().y);
		rightLimit_ = transformRf_->getPosition().x + width_;
		x_ = transformRf_->getPosition().x;
		slider_->setLeftLimit(x_);
		slider_->setRightLimit(rightLimit_);

		//ZOrder syncing
		slider_->setRenderOrder(transformRf_->getPosition().z + 10);
	}
	void Slider::setSliderClick(std::function<void(std::string, float)> function)
	{
		onSliderClick = function;
	}
	void Slider::setDimensions(float width, float height)
	{
		slider_->setPosition(x_ + (slider_->getRelativePos() / 100) * width, y_);
		width_ = width;
		height_ = height;
		slider_->setSize(width, height);
		rightLimit_ = x_ + width;

		progressBar_->setDimensions(width, height);
		background_->setDimensions(width, height);
	}
}
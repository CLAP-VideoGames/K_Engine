#include "UIElement.h"

#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreRenderTarget.h>
#include <OgreOverlayManager.h>
#include <OgreTextAreaOverlayElement.h>

#include <render_prj/RenderManager.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
	UIElement::UIElement(Ogre::OverlayManager* man)
	{
		oveMngr_ = man;

		size = std::pair<int, int>(defaultWidth, defaultHeight);

		position = std::pair<int, int>(defaultX, defaultY);
	}

	UIElement::~UIElement() = default;

	void UIElement::show()
	{
		overlay_->show();
	}

	void UIElement::hide()
	{
		overlay_->hide();
	}

	void UIElement::setMaterial(std::string const& materialName)
	{
		element_->setMaterialName(materialName);
	}

	std::pair<int, int> UIElement::getPosition()
	{

		return position;
	}

	std::pair<int, int> UIElement::getSize()
	{
		return size;
	}

	void UIElement::setPosition(int x, int y)
	{
		element_->setPosition(x, y);

		position.first = x;
		position.second = y;
	}

	void UIElement::setSize(int w, int h)
	{
		element_->setDimensions(w, h);

		size.first = w;
		size.second = h;
	}

	void UIElement::setMetrics(Metrics m)
	{
		if (m == Pixels) element_->setMetricsMode(Ogre::GMM_PIXELS);
		else if (m == WindowRelative) element_->setMetricsMode(Ogre::GMM_RELATIVE);
	}

	void UIElement::setRenderOrder(int z)
	{
		overlay_->setZOrder(z);
	}
}
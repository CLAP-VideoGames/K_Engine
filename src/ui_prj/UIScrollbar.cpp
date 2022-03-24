#include "UIScrollBar.h"
#include "UIManager.h"

#include <CEGUI/CEGUI.h>

UIScrollbar::UIScrollbar(CEGUI::WindowManager* winMngr, CEGUI::DefaultWindow* mRoot, std::string& schemeName, Vector2 pos_, Vector2 size_, std::string name_, float v)
	: UIComponent(winMngr, mRoot, schemeName,pos_, size_, name_), value(v)
{
    //Creation from the scheme
    uiWindow = (CEGUI::Scrollbar*)winMngr->createWindow(schemeName + "/Spinner");

    //Adding as a child so we see it
    mRoot->addChild(uiWindow);

    //Position
    uiWindow->setPosition(CEGUI::UVector2(cegui_reldim(pos.first), cegui_reldim(pos.second)));

    //You cannot change the size of a text in CEGUI for some reason
    uiWindow->setSize(CEGUI::USize(cegui_reldim(size.first), cegui_reldim(size.second)));
}

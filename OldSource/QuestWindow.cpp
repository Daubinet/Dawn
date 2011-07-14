#include "QuestWindow.h"
#include "EventReceiver.h"
#include "Globals.h"

QuestWindow::QuestWindow(std::string filename)
{
	_visible = true;
	_window.setTexture("../../Data/Hud/Quest.png");

	_buttonExit.UpperLeftCorner = vector2d<s32>(230, 2);
	_buttonExit.LowerRightCorner = vector2d<s32>(250, 28);
}

QuestWindow::~QuestWindow()
{
}

void QuestWindow::handleEvents()
{
	if(gEventReceiver.mouseClickLeft())
	{
		int x = gEventReceiver.mouseX();
		int y = gEventReceiver.mouseY();

		if(_buttonExit.isPointInside(vector2d<s32>(x, y)))
		killme();
	}
}

void QuestWindow::draw()
{
	if(_visible) {
		_window.draw();
	}
}
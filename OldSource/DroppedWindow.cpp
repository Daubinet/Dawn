#include "GameInfo.h"
#include "Globals.h"
#include "EventReceiver.h"
#include "DroppedWindow.h"

DroppedWindow::DroppedWindow(vector3df position3D)
{
	_visible = true;
	_window.setTexture("../../Data/Hud/Dropped.png", true);

	Item item;
	item.loadItem("../../Database/Items/SH00001.txt");
	item.setPosition(20, 60);
	_items.push_back(item);

	Item item2;
	item2.loadItem("../../Database/Items/SH00002.txt");
	item2.setPosition(90, 60);
	_items.push_back(item2);

	_selectedItem = -1;
	_selection.setTexture("../../Data/Hud/Items/Selection.png", true);

	_buttonExit.UpperLeftCorner = vector2d<s32>(331, 8);
	_buttonExit.LowerRightCorner = vector2d<s32>(360, 31);

	_position3D = position3D;
}

DroppedWindow::~DroppedWindow()
{
}

void DroppedWindow::handleEvents()
{	
	if((distance(gGameInfo.heroPosition(), _position3D) > 10.0))
	{
		killme();
	}


	if(gEventReceiver.mouseClickLeft())
	{
		int x = gEventReceiver.mouseX();
		int y = gEventReceiver.mouseY();

		if (_buttonExit.isPointInside(vector2d<irr::s32>(x,y)))
		{
			killme();
		}

	for(size_t i = 0; i < _items.size(); ++i)
		{
			if(_items[i].isColliding(x, y))
			{
				_selectedItem = i;
				_selection.setPosition(_items[i].position());
			}
		}

				for(size_t i = 0; i < _items.size(); ++i)
				{
					if(_items[i].isColliding(x, y))
					{
					}
				}
	}	
}

void DroppedWindow::draw()
{
	if(_visible) {
		_window.draw();

		for(size_t i = 0; i < _items.size(); ++i)
			_items[i].draw();
		
		if(_selectedItem != -1)
			_selection.draw();

	}
}

#include "Globals.h"
#include "EventReceiver.h"
#include "SellingWindow.h"

SellingWindow::SellingWindow(std::string filename)
{
	_visible = true;
	_window.setTexture("../../Data/Hud/Selling.png", true);

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

	_buttonBuy.UpperLeftCorner =vector2d<s32>(242, 336);
	_buttonBuy.LowerRightCorner = vector2d<s32>(339, 384);

	_inventory.show();
}

SellingWindow::~SellingWindow()
{
}

void SellingWindow::handleEvents()
{
	if(gEventReceiver.mouseClickLeft())
	{
		int x = gEventReceiver.mouseX();
		int y = gEventReceiver.mouseY();

		for(size_t i = 0; i < _items.size(); ++i)
		{
			if(_items[i].isColliding(x, y))
			{
				_selectedItem = i;
				_selection.setPosition(_items[i].position());
				_priceText = toString(_items[i].price());
			}
		}

		if(_buttonBuy.isPointInside(vector2d<s32>(x, y)))
		{
			if(_inventory.addItem(_items[_selectedItem], _items[_selectedItem].price()) && _selectedItem != -1)
				msg ="The items is yours now";
			else
				msg = "You havent enough gold !";
		}

		if(_buttonExit.isPointInside(vector2d<s32>(x, y)))
			killme();
	}
}

void SellingWindow::draw()
{
	if(_visible) {
		_window.draw();
		_inventory.draw();


		for(size_t i = 0; i < _items.size(); ++i)
			_items[i].draw();

		if(_selectedItem != -1)
			_selection.draw();
		if(!msg.empty())
		gText.draw(msg, (gScreenWidth /2) -200 , gScreenHeight / 2);

		gText.draw(_priceText, 92, 337);
	}
}

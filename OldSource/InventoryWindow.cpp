#include "Globals.h"
#include "Hud.h"
#include "InventoryWindow.h"
#include "SceneManager.h"
#include "Text.h"

InventoryWindow::InventoryWindow()
{
	_visible = false;

	_inventory.setTexture("../../Data/Hud/Inventory.png");
	_inventory.setPosition(gScreenWidth-_inventory.width(), 0);

	_itemWidth = _inventory.position().X +25;
	_itemHeight = _inventory.position().Y +25;
}

InventoryWindow::~InventoryWindow()
{
}

void InventoryWindow::handleEvents()
{
	if(gEventReceiver.keyPress(irr::KEY_KEY_I))
		_visible = !_visible;
	if(!_visible) return;

	if(gEventReceiver.mouseClickLeft())
	{
		for(size_t coll = 0; coll < _invItems.size(); ++coll)
		{
			//if(_invItems[coll].isColliding(gEventReceiver.mouseX(), gEventReceiver.mouseY()))
				//gSceneManager.setCursor(_invItems[coll].sprite());
		}
	}
}

void InventoryWindow::draw()
{
	if(!_visible) return;

	_inventory.draw();
	gText.draw("Inventory", gScreenWidth-300, 20);
	gText.draw(toString(gGameInfo.hero()->gold()), gScreenWidth-100, 300);
}
bool InventoryWindow::addItem(Item item, int cost)
{

	//TODO Add the image to the inventory
	if(gGameInfo.hero()->gold() >= cost ){
	item.setPosition(_itemWidth, _itemHeight);
	_itemWidth += 50;

	if((_itemWidth - _inventory.position().X ) >= 200)
	{
		_itemWidth -=200;
		_itemHeight +=50;
	}
	_invItems.push_back(item);
	return true;
	}
	else
		return false;
}
bool InventoryWindow::deleteItem()
{
	// TO DO DELETE FROM _invItems

	return false;
}

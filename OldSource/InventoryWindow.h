#ifndef __INVENTORYWINDOW_H
#define __INVENTORYWINDOW_H

#include <vector>
#include "Item.h"
#include "Sprite2D.h"
#include "Window.h"

class InventoryWindow : public Window
{
public:
	InventoryWindow();
	~InventoryWindow();

	bool addItem(Item item, int cost);
	bool deleteItem();

	virtual void handleEvents();
	virtual void draw();

private:
	// Inventory
	enum InventoryCollision
	{
		ICNone,
		ICHelmet,
		ICArmor,
		ICWeapon1,
		ICWeapon2,
		ICSize
	};

	Sprite2D _inventory;
	std::vector<Item> _invItems;
	
	int _itemWidth;
	int _itemHeight;
};

#endif // __INVENTORYWINDOW_H
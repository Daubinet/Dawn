#ifndef __SELLINGWINDOW_H
#define __SELLINGWINDOW_H

#include <string>
#include <vector>
#include "Item.h"
#include "Sprite2D.h"
#include "Text.h"
#include "Window.h"
#include "InventoryWindow.h"

class SellingWindow : public Window
{
public:
	SellingWindow(std::string filename);
	~SellingWindow();

	virtual void handleEvents();
	virtual void draw();

private:
	Sprite2D _window;

	std::string _priceText;

	rect<s32> _buttonExit;
	rect<s32> _buttonBuy;


	std::vector< rect<s32> > _itemRects;
	std::vector<Item> _items;
	int _selectedItem;
	Sprite2D _selection;
	InventoryWindow _inventory;
	std::string msg;
};

#endif //__SELLINGWINDOW_H
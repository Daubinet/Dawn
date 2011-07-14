#ifndef __DROPPEDWINDOW_H
#define __DROPPEDWINDOW_H

#include <string>
#include <vector>
#include "Item.h"
#include "Sprite2D.h"
#include "Text.h"
#include "Window.h"

class DroppedWindow : public Window
{
public:
	DroppedWindow(vector3df position3D);
	~DroppedWindow();

	virtual void handleEvents();
	virtual void draw();

private:
	Sprite2D _window;

	rect<s32> _buttonExit;
	std::vector< rect<s32> > _itemRects;
	std::vector<Item> _items;
	int _selectedItem;
	Sprite2D _selection;
};

#endif //__DROPPEDWINDOW_H
#ifndef __ITEM_H
#define __ITEM_H

#include <string>
#include "Sprite2D.h"

class Item
{
public:
	Item();
	~Item();

	void loadItem(std::string filename);
	void draw();

	bool isColliding(int x, int y);

	// Gets
	int price() { return _price; }
	position2d<s32> position() { return _sprite.position(); }

	// Sets
	void setPosition(int x, int y) { _sprite.setPosition(x, y); }
	

private:
	std::string _code;
	int _price;

	Sprite2D _sprite;
};

#endif //__ITEM_H
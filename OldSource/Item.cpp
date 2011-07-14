
#include <fstream>
#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}

bool Item::isColliding(int x, int y)
{
	return _sprite.isColliding(x, y);
}

void Item::draw()
{
	_sprite.draw();
}

void Item::loadItem(std::string filename)
{
	std::ifstream input(filename.c_str());

	std::string str;
	while(input >> str)
	{
		if(str == "Icon") {
			std::string file;
			input >> file;
			_sprite.setTexture("../../Data/Hud/Items/"+file, true);
			continue;
		}
		if(str == "Price") { 
			input >> _price;
			continue;
		}
	}
}
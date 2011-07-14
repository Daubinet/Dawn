#ifndef __TEXT_H
#define __TEXT_H

#include <string>
#include <vector>
#include "Sprite2D.h"

class Text
{
public:
	Text();
	~Text();

	void initialize();
	void draw(std::string gText, int x, int y, int width=100, int height=100);

private:
	gui::IGUIFont *font;
};



#endif // __TEXT_H
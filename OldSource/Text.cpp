#include "Globals.h"
#include "Text.h"

using namespace irr;
using namespace core;

Text::Text()
{
}

Text::~Text()
{
}

void Text::initialize()
{
	font = gDevice->getGUIEnvironment()->getFont("../../Data/Fonts/Title.xml"); 
}

void Text::draw(std::string gText, int x, int y, int width, int height)
{
	stringw textW(gText.c_str());
	font->draw(textW, core::rect<s32>(x,y,width,height), video::SColor(255,255,255,255));
}


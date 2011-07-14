#include "Globals.h"
#include "Sprite2D.h"

using namespace irr;
using namespace core;
using namespace video;

Sprite2D::Sprite2D()
{
}

Sprite2D::~Sprite2D()
{
}

bool Sprite2D::isColliding(int x, int y)
{
	rect<s32> r(_position, _size);
	return r.isPointInside(vector2d<s32>(x, y));
}

void Sprite2D::setTexture(std::string filename, bool transparent) 
{ 
	_tex = gRender->getTexture(filename.c_str()); 
	_size = _tex->getOriginalSize();
	
	if(transparent)
		gRender->makeColorKeyTexture(_tex, core::position2d<s32>(0,0));

}

void Sprite2D::draw()
{
	rect<s32> r(vector2d<s32>(0, 0), _size);
	gRender->draw2DImage(_tex, _position, r, 0, SColor(255,255,255,255), true);
}
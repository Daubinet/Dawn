#ifndef __SPRITE2D_H
#define __SPRITE2D_H

#include <string>
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;

class Sprite2D
{
public:
	Sprite2D();
	~Sprite2D();

	void draw();

	// Sets
	void setTexture(std::string filename, bool transparent = false);
	void setPosition(int x, int y) { _position = vector2d<int>(x, y); }
	void setPosition(position2d<s32> position) { _position = position; }
	void setSize(int x, int y) { _size = vector2d<int>(x, y); }

	// Gets
	position2d<s32> position() { return _position; }
	inline int width() const { return _size.Width; }
	inline int height() const { return _size.Height; }
	bool isColliding(int x, int y);

private:
	ITexture *_tex;
	position2d<s32> _position;
	dimension2d<s32> _size;
};

#endif //__SPRITE2D_H
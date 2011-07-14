#ifndef __WINDOW_H
#define __WINDOW_H

#include <irrlicht.h>

using namespace irr;
using namespace core;

class Hud;

class Window
{
public:
	Window();
	~Window();

	virtual void handleEvents() = 0;
	virtual void draw() = 0;

	// Gets
	bool dead() { return _dead; }
	vector3df position3D() { return _position3D; }

	// Sets
	void setPosition3D(vector3df position3D) { _position3D = position3D; }
	void show() { _visible = true; }
	void hide() { _visible = false; }
	void killme() { _dead = true; }

protected:
	Hud *_hud;
	bool _visible, _dead;
	vector3df _position3D;
};

#endif // __Window_H

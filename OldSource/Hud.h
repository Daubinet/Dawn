/*
Hud
*/

#ifndef __HUD_H
#define __HUD_H

#include <list>
#include <vector>
#include <irrlicht.h>
#include "EventReceiver.h"
#include "GameInfo.h"
#include "Window.h"
#include "Sprite2D.h"

using namespace irr;
using namespace video;

class Hud
{
public:
	Hud();
	~Hud();

	bool initialize();

	void handleEvents();
	void update();
	void draw();
	
	void addWindow(Window *window);
	
private:
	std::list<Window*> _windows;
};

#endif
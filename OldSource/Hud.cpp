#include <list>
#include <irrlicht.h>
#include "Globals.h"
#include "Hud.h"
#include "HudWindow.h"
#include "InventoryWindow.h"
#include "Window.h"

using namespace irr;

Hud::Hud()
{
}

Hud::~Hud()
{
}

bool Hud::initialize()
{
	InventoryWindow *inv = new InventoryWindow();
	_windows.push_back(inv);

	HudWindow *hud = new HudWindow();
	_windows.push_back(hud);

	return true;
}

void Hud::addWindow(Window *window)
{
	_windows.push_back(window);
}

void Hud::handleEvents()
{
	std::list<Window*>::iterator it;
	for(it = _windows.begin(); it != _windows.end(); ++it)
		(*it)->handleEvents();
}

void Hud::update()
{
}

void Hud::draw()
{
	std::list<Window*>::iterator it;

	for(it = _windows.begin(); it != _windows.end(); ++it) {

		if((*it)->dead()) {
			_windows.erase(it);
			it = _windows.begin();
		}
	}

	for(it = _windows.begin(); it != _windows.end(); ++it) {
		(*it)->draw();
	}
}

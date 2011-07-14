/*
authors Soulmen
*/

#ifndef __MENU_INTERFACE_INCLUDED
#define __MENU_INTERFACE_INCLUDED

#include <irrlicht.h>
#include "EventReceiver.h"
#include "Sprite2D.h"

class SceneManager;

class Menu
{
public:
	// Create/destroy
	Menu();
	~Menu();

	bool initialize();

	void handleEvents();
	void draw();
	void update();

private:
	Sprite2D texture;

	irr::gui::IGUIButton* exit;
	irr::gui::IGUIButton* logout;
};


#endif
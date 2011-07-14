#ifndef __HUDWINDOW_H
#define __HUDWINDOW_H

#include <string>
#include "Window.h"
#include "Sprite2D.h"

class HudWindow : public Window
{
public:
	HudWindow();
	~HudWindow();

	virtual void handleEvents();
	virtual void draw();

private:
	Sprite2D _window;
	Sprite2D _icon, _enemyIcon;
	Sprite2D _life, _enemyLife, _lifeBar1, _lifeBar2;
	Sprite2D _xpBar, _xpBack, _xp;
};

#endif //__HUDWINDOW_H
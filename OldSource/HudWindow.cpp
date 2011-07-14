#include "GameInfo.h"
#include "Globals.h"
#include "HudWindow.h"

HudWindow::HudWindow()
{
	_visible = true;
	
	_xpBar.setTexture("../../Data/Hud/XPBar.png", true);
	_xpBar.setPosition((gScreenWidth-_xpBar.width())/2, gScreenHeight-_xpBar.height());
	_xpBack.setTexture("../../Data/Hud/XPBack.png");
	_xpBack.setPosition(_xpBar.position());
	_xpBack.setSize(_xpBar.width(), _xpBack.height());
	_xp.setTexture("../../Data/Hud/XP.png");
	_xp.setPosition(_xpBar.position());

	_window.setTexture("../../Data/Hud/Hud.png", true);
	_window.setPosition((gScreenWidth-_window.width())/2, gScreenHeight-_window.height()-_xpBar.height());

	_icon.setTexture("../../Data/Chars/HumanIcon.png");
	_life.setTexture("../../Data/Hud/Life.png");
	_enemyLife.setTexture("../../Data/Hud/EnemyLife.png");
	_lifeBar1.setTexture("../../Data/Hud/LifeBar.png");
	_lifeBar2.setTexture("../../Data/Hud/LifeBar.png");
	
	_lifeBar1.setPosition(75, 19);
	_lifeBar2.setPosition(275, 19);
	_lifeBar1.setSize(100, 20);
	_lifeBar2.setSize(100, 20);

	_icon.setPosition(5, 5);
	_life.setPosition(75, 20);
	_enemyLife.setPosition(275, 20);
}

HudWindow::~HudWindow()
{
}

void HudWindow::handleEvents()
{
	_life.setSize(gGameInfo.life(), _life.height());
	_enemyLife.setSize(gGameInfo.enemyLife(), _enemyLife.height());
	_xp.setSize(gGameInfo.xp(), _xp.height());
}

void HudWindow::draw()
{
	if(_visible) {
		_window.draw();

		_icon.draw();
		_lifeBar1.draw();
		_lifeBar2.draw();

		_life.draw();
		_enemyLife.draw();

		_xpBack.draw();
		_xp.draw();
		_xpBar.draw();
	}
}
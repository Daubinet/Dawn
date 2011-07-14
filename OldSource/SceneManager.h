/*
SceneManager.h
*/

#ifndef __SCENEMANAGER_H
#define __SCENEMANAGER_H

#include <list>
#include <irrlicht.h>

#include "CharSelection.h"
#include "EventReceiver.h"
#include "GameInfo.h"
//#include "Login.h"
#include "Menu.h"
#include "Hud.h"
#include "Game.h"

using namespace irr;
using namespace video;

class SceneManager
{
public:
	enum ContextID {
		CTX_LOGIN,
		CTX_CHARSELECTION,
		CTX_MENU,
		CTX_GAME,
		CTX_NUMBER
	};

	SceneManager();
	~SceneManager();

	bool initialize();
	void deinitialize();

	void setCursor(Sprite2D cursor);
	void setContext(ContextID context);

	void handleEvents(f32);
	void update(f32);
	void draw();

private:
	Sprite2D _cursor;
	ContextID _context;
	bool _isInitialized[CTX_NUMBER];

//	Login _login;
	Menu _menu;
	Game _scene;
	CharSelection _charSelection;

	friend class Protocol;
};

#endif // __SCENEMANAGER_H
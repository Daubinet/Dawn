#include "Globals.h"
#include "SceneManager.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

bool SceneManager::initialize()
{
	_context = CTX_CHARSELECTION;
	_charSelection.initialize();
	_isInitialized[CTX_CHARSELECTION] = true;
	
	_cursor.setTexture("../../Data/Hud/Cursor.png", true);
		
	return true;
}

void SceneManager::handleEvents(f32 timeScale)
{
	switch(_context)
	{
		case CTX_LOGIN:
			//_login.handleEvents();
			break;
		case CTX_CHARSELECTION:
			_charSelection.handleEvents();
			break;
		case CTX_GAME:
			_scene.handleEvents(timeScale);
			break;
		case CTX_MENU:
			_menu.handleEvents();
			break;
	}

	_cursor.setPosition(gEventReceiver.mouseX(), gEventReceiver.mouseY());
}

void SceneManager::update(f32 timeScale)
{
	switch(_context)
	{
		case CTX_LOGIN:
			//_login.update();
			break;
		case CTX_CHARSELECTION:
			_charSelection.update();
			break;
		case CTX_GAME:
			_scene.update(timeScale);
			break;
		case CTX_MENU:
			_scene.update();
			_menu.update();
			break;
	}
}

void SceneManager::draw()
{
	gRender->beginScene(true, true, video::SColor(255, 0, 0, 255));
	
	switch(_context)
	{
		case CTX_LOGIN:
			//_login.draw();
			break;
		case CTX_CHARSELECTION:
			_charSelection.draw();
			break;
		case CTX_GAME:
			_scene.draw();
			break;
		case CTX_MENU:
			_scene.draw();
			_menu.draw();
			break;
	}

	_cursor.draw();
			
	gRender->endScene();
}

void SceneManager::setContext(ContextID context) 
{ 
	_context = context;
	if(!_isInitialized[context])
	{
		switch(_context)
		{
			case CTX_LOGIN:
				//_login.initialize();
				_isInitialized[CTX_LOGIN] = true;
				break;
			case CTX_CHARSELECTION:
				_charSelection.initialize();
				_isInitialized[CTX_CHARSELECTION] = true;
				break;
			case CTX_GAME:
				_scene.initialize();
				_isInitialized[CTX_GAME] = true;
				break;
			case CTX_MENU:
				_menu.initialize();
				_isInitialized[CTX_MENU] = true;
				break;
		}
	}
}

void SceneManager::setCursor(Sprite2D cursor)
{
	_cursor = cursor;
}

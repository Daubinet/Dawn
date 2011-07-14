#ifndef __APP_H
#define __APP_H

#include "Game.h"
#include "EventManager.h"
#include "Ogre.h"
#include "OgreWindowEventUtilities.h"

class App
{
public:
	App();
	~App();

	void initialize();
	void mainLoop();

private:
	Ogre::Root *ogre;
	Ogre::RenderWindow *window;
	Ogre::SceneManager *sceneMgr;
	Ogre::Camera *camera;
	EventManager *handler;

	Game game;
};

#endif // __APP_H
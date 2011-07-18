#ifndef __APP_H
#define __APP_H

#include <Ogre.h>
#include <OgreTimer.h>
#include <OgreWindowEventUtilities.h>
#include "Game.h"
#include "EventManager.h"

class App
{
public:
	App();
	~App();

	void initialize();
	void mainLoop();
	void destroyWindow();

private:
	Ogre::Root *ogre;
	Ogre::RenderWindow *window;
	Ogre::SceneManager *sceneMgr;
	Ogre::Camera *camera;
	EventManager *handler;

	Ogre::Timer _timer;
	Game game;
};

#endif // __APP_H
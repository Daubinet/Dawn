#ifndef __GAME_H
#define __GAME_H

#include <Ogre.h>
#include <OgreWindowEventUtilities.h>
#include "EventManager.h"

class Game
{
public:
    Game(void);
    virtual ~Game(void);

	void initialize(Ogre::SceneManager *sceneManager, Ogre::Camera *camera, EventManager *handler);
	void update();
	void draw();

private:
	Ogre::SceneManager *_sceneManager;
	Ogre::Camera *_camera;
	EventManager *_handler;

};

#endif // __GAME_H

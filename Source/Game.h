#ifndef __GAME_H
#define __GAME_H

#include <Ogre.h>
#include <OgreWindowEventUtilities.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include "EventManager.h"
#include "StaticObject.h"
#include "AnimatedObject.h"

class Game
{
public:
    Game(void);
    virtual ~Game(void);

	void initialize(Ogre::Camera *camera, EventManager *handler);
	void update(unsigned long milliseconds);

private:
	Ogre::Camera *_camera;
	EventManager *_handler;

	AnimatedObject robot;
	AnimatedObject werewolf;
	StaticObject streetLamp, sellingHouse;

	Ogre::TerrainGlobalOptions *mTerrainGlobals;
	Ogre::TerrainGroup *mTerrainGroup;
	bool mTerrainsImported;
	void defineTerrain(long x, long y);
	void initBlendMaps(Ogre::Terrain* terrain);
	void configureTerrainDefaults(Ogre::Light* light); 
};

#endif // __GAME_H

#ifndef __GAME_H
#define __GAME_H

#include <Ogre.h>
#include <OgreWindowEventUtilities.h>
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>
#include "EventManager.h"
#include "StaticObject.h"
#include "Player.h"
#include "Mob.h"

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

	Player _werewolf;
	Mob _monster;
	StaticObject _streetLamp, _sellingHouse;

	Ogre::TerrainGlobalOptions *mTerrainGlobals;
	Ogre::TerrainGroup *mTerrainGroup;
	bool mTerrainsImported;
	void defineTerrain(long x, long y);
	void initBlendMaps(Ogre::Terrain* terrain);
	void configureTerrainDefaults(Ogre::Light* light); 
};

#endif // __GAME_H

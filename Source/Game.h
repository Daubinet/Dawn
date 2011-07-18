#ifndef __GAME_H
#define __GAME_H

#include <Ogre.h>
#include <OgreWindowEventUtilities.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include "EventManager.h"
#include "StaticObject.h"

class Game
{
public:
    Game(void);
    virtual ~Game(void);

	void initialize(Ogre::SceneManager *sceneManager, Ogre::Camera *camera, EventManager *handler);
	void update(unsigned long milliseconds);
	void draw();

private:
	Ogre::SceneManager *_sceneManager;
	Ogre::Camera *_camera;
	EventManager *_handler;
	StaticObject* _ninja;

	Ogre::TerrainGlobalOptions *mTerrainGlobals;
	Ogre::TerrainGroup *mTerrainGroup;
	bool mTerrainsImported;
	void defineTerrain(long x, long y);
	void initBlendMaps(Ogre::Terrain* terrain);
	void configureTerrainDefaults(Ogre::Light* light); 

};

#endif // __GAME_H

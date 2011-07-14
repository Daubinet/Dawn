#ifndef __SCENE_H
#define __SCENE_H

#include <vector>
#include <list>
#include "AnimObject.h"
#include "StaticObject.h"
#include "Camera.h"
#include "Light.h"
#include "EventReceiver.h"
#include "GameInfo.h"
#include "Hero.h"
#include "Hud.h"
#include "MOB.h"
#include "NPC.h"
#include "Menu.h"
#include "Terrain.h"
#include "Water.h"

using namespace irr;
using namespace video;
using namespace scene;

class Game
{
public:
	Game();
	~Game();

	bool initialize();

	void handleEvents(f32);
	void update(f32 time = 0.0f);
	void draw();

private:
	Hud _hud;

	ISceneManager *_sceneIrr;
	ICameraSceneNode *_camera;
	ITriangleSelector *_selector;
	ISceneNode *_selectedSceneNode;

	bool _changedSelection;

	Light _light;
	Terrain *_terrain;
	Water _water;

	Hero *_hero;
	std::vector<MOB*> _mobs;
	std::vector<NPC*> _npcs;
	std::vector<StaticObject*> _objs;
};

#endif

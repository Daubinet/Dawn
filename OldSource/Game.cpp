#include <iostream>
#include <irrlicht.h>
#include "AnimObject.h"
#include "StaticObject.h"
#include "Globals.h"
#include "DatabaseConstants.h"
#include "QuestWindow.h"
#include "SellingWindow.h"
#include "DroppedWindow.h"
#include "SceneManager.h"
#include "Terrain.h"
#include "Water.h"
#include "Sprite3D.h"
#include "Particles.h"
#include "Game.h"

using namespace irr;
using namespace scene;

Game::Game()
: _changedSelection(false)
{
}

Game::~Game()
{
}

bool Game::initialize()
{
	_sceneIrr = gDevice->getSceneManager();
	_sceneIrr->clear();
	
	// load region
	gGameInfo.addHero(0);
	gGameInfo.loadRegion(0);

	_terrain = new Terrain("../../Database/Dunes2.bmp", _sceneIrr->getRootSceneNode(), _sceneIrr, 666);

	//_water.initialize(_sceneIrr);
	
	_hero = new Hero("../../Data/Chars/Werewolf.x", "../../Data/Chars/Billboard.png", _sceneIrr->getRootSceneNode(), _sceneIrr, ObjectType::OBJ_None);
	_hero->loadAnimInfo("../../Data/Chars/Werewolf.ancfg");
	_hero->setStats(gGameInfo.hero());
    core::vector3df heroPosition = gGameInfo.heroPosition();
    _terrain->getHeight(heroPosition);
	_hero->setPosition(heroPosition);
	_hero->setMoveSpeed(PLAYER_MOVE_SPEED);
	_hero->setRotSpeed(PLAYER_ROT_SPEED);
	_hero->stop();

	Sprite3D sprite3D;
	sprite3D.createMaterials("../../Data/Shaders/sprite3d.hlsl", "../../Data/Shaders/sprite3d.hlsl");

	scene::ISceneNode* node = _sceneIrr->addCubeSceneNode(1, 0, -1, vector3df(0,0,0), vector3df(0,0,0), vector3df(10, 10, 0.01));
	node->setPosition(core::vector3df(100,20,-40));
	node->setMaterialTexture(0, gRender->getTexture("../../Data/Textures/grass.png"));
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setMaterialType((video::E_MATERIAL_TYPE)(sprite3D.newMaterialType1()));

	for(int i = 0; i < gGameInfo.nMobs(); ++i) {
		MOB *mob = new MOB(gDB.getMeshFromId(gGameInfo.mobs(i)->dbId()), gDB.getBillboardFromId(gGameInfo.mobs(i)->dbId()), _sceneIrr->getRootSceneNode(), _sceneIrr, ObjectType::OBJ_MOB); 
		mob->loadAnimInfo(gDB.getAnimInfoFromId(gGameInfo.mobs(i)->dbId()));
		mob->setMoveSpeed(MOB_MOVE_SPEED);
		mob->setRotSpeed(MOB_ROT_SPEED);
		mob->setStats(gGameInfo.mobs(i));
		mob->stop();
		mob->patrollArea(mob->getPosition().X, mob->getPosition().Z, 10.0f);
		_mobs.push_back(mob);

		_selector = _sceneIrr->createTriangleSelector(mob);
		mob->setTriangleSelector(_selector);
		_selector->drop();
	}

	for(int i = 0; i < gGameInfo.nNpcs(); ++i) {
	
		NPC *npc = new NPC(gDB.getMeshFromId(gGameInfo.npcs(i)->dbId()), gDB.getBillboardFromId(gGameInfo.npcs(i)->dbId()), _sceneIrr->getRootSceneNode(), _sceneIrr, ObjectType::OBJ_NPC_SELL); 
		npc->loadAnimInfo(gDB.getAnimInfoFromId(gGameInfo.npcs(i)->dbId()));
		npc->setStats(gGameInfo.npcs(i));
		npc->stop();
		_npcs.push_back(npc);
	
		_selector = _sceneIrr->createTriangleSelector(npc);
		npc->setTriangleSelector(_selector);
		_selector->drop();
	}

	// hack
	Particles p;
	p.setFire(_sceneIrr);
	p.setPosition(core::vector3df(140,10,-150));

	StaticObject *store = new StaticObject("../../Data/SellingHouse.obj", _sceneIrr->getRootSceneNode(), _sceneIrr);
	store->setPosition(vector3df(195, 0, -110));
	store->setRotation(vector3df(0, -90, 0));

	StaticObject *tree = new StaticObject("../../Data/Tree.obj", _sceneIrr->getRootSceneNode(), _sceneIrr);
	tree->setPosition(vector3df(135, 0, -100));

	StaticObject *tree2 = new StaticObject("../../Data/Tree.obj", _sceneIrr->getRootSceneNode(), _sceneIrr);
	tree2->setPosition(vector3df(155, 0, -100));

	StaticObject *tree3 = new StaticObject("../../Data/Tree.obj", _sceneIrr->getRootSceneNode(), _sceneIrr);
	tree3->setPosition(vector3df(145, 0, -70));

	StaticObject *streetLamp = new StaticObject("../../Data/StreetLamp1.obj", _sceneIrr->getRootSceneNode(), _sceneIrr);
	streetLamp->setPosition(vector3df(152, 0, -50));
	streetLamp->setRotation(vector3df(0, 90, 0));

	StaticObject *streetLamp2 = new StaticObject("../../Data/StreetLamp1.obj", _sceneIrr->getRootSceneNode(), _sceneIrr);
	streetLamp2->setPosition(vector3df(172, 0, 100));
	streetLamp2->setRotation(vector3df(0, -90, 0));

	ISceneNode* skybox=_sceneIrr->addSkyBoxSceneNode(
		gRender->getTexture("../../Data/irrlicht2_up.jpg"),
		gRender->getTexture("../../Data/irrlicht2_dn.jpg"),
		gRender->getTexture("../../Data/irrlicht2_lf.jpg"),
		gRender->getTexture("../../Data/irrlicht2_rt.jpg"),
		gRender->getTexture("../../Data/irrlicht2_ft.jpg"),
		gRender->getTexture("../../Data/irrlicht2_bk.jpg"));

	_camera = _sceneIrr->addCameraSceneNode(0, _hero->getPosition() + vector3df(0, 15, -20), _hero->getPosition());
	_sceneIrr->addLightSceneNode(0, core::vector3df(0,2000,0), video::SColorf(1.0f,1.0f,1.0f,1.0f), 20000.0f);

	_hud.initialize();
	return true;
}

void Game::handleEvents(f32 timeScale)
{
	bool stop = true;
	if(gEventReceiver.isPressingKey(irr::KEY_KEY_W) || gEventReceiver.isPressingKey(irr::KEY_UP)) {
		_hero->walk(timeScale);
        core::vector3df position = _hero->getPosition();
        _terrain->getHeight(position);
        _hero->setPosition(position);
		stop = false;
	}
	if(gEventReceiver.isPressingKey(irr::KEY_KEY_A) || gEventReceiver.isPressingKey(irr::KEY_LEFT)) {
		_hero->turnLeft(timeScale);
		stop = false;
	}
	if(gEventReceiver.isPressingKey(irr::KEY_KEY_D) || gEventReceiver.isPressingKey(irr::KEY_RIGHT)) {
		_hero->turnRight(timeScale);
		stop = false;
	}
	if(_hero->isAttacking())
		stop = false;

	if(gEventReceiver.keyPress(irr::KEY_ESCAPE))
    {
		gSceneManager.setContext(SceneManager::CTX_MENU);
    }
	if(stop)
		_hero->stop();

	if(gEventReceiver.mouseClickLeft())
	{
		scene::ISceneCollisionManager* collMan = _sceneIrr->getSceneCollisionManager();
		core::line3d<f32> ray = collMan->getRayFromScreenCoordinates(vector2d<s32>(gEventReceiver.mouseX(), gEventReceiver.mouseY()), _camera);
		core::vector3df intersection;
		core::triangle3df hitTriangle;

		// select mob
		_selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, ObjectType::OBJ_MOB);
		if(_selectedSceneNode) {
			((MOB*)_selectedSceneNode)->select();
			gGameInfo.setSelected(((MOB*)_selectedSceneNode)->index());
			_changedSelection = true;
			return;
		}

		// select npc quest
		_selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, ObjectType::OBJ_NPC_QUEST);
		if(_selectedSceneNode) {
			((NPC*)_selectedSceneNode)->select();
			gGameInfo.setSelected(((NPC*)_selectedSceneNode)->index());
			_changedSelection = true;
			return;
		}

		// select npc sell
		_selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, ObjectType::OBJ_NPC_SELL);
		if(_selectedSceneNode) {
			((NPC*)_selectedSceneNode)->select();
			gGameInfo.setSelected(((NPC*)_selectedSceneNode)->index());
			_changedSelection = true;
			return;
		}

		// select collectable
		_selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, ObjectType::OBJ_COLLECT);
		if(_selectedSceneNode) {
			//((StaticObject*)_selectedSceneNode)->select();
			gGameInfo.setSelected(_selectedSceneNode->getID());
			_changedSelection = true;
			return;
		}
	}

	_hud.handleEvents();
}

void Game::update(f32 timeScale)
{
	_camera->setPosition(_hero->getPosition() + vector3df(0, 20, -20));
	_camera->setTarget(_hero->getPosition() + vector3df(0, 10, 0));

	if(_changedSelection)
	{
		if(distance(_hero->getPosition(), _selectedSceneNode->getPosition())<15.0)
		{
			if(_selectedSceneNode->getID() == ObjectType::OBJ_NPC_SELL)
				_hud.addWindow(new SellingWindow("haha"));

			if(_selectedSceneNode->getID() == ObjectType::OBJ_NPC_QUEST)
				_hud.addWindow(new QuestWindow("haha"));

			if(_selectedSceneNode->getID() == ObjectType::OBJ_MOB) {
				_hero->attack(timeScale);
			}

			if(_selectedSceneNode->getID() == ObjectType::OBJ_COLLECT) {
				DroppedWindow *drop = new DroppedWindow(_selectedSceneNode->getPosition());
				_hud.addWindow(drop);
			}
		}		
	}

	if(_hero->attacked())
	{
		if(_hero->getAttackArea().intersectsWithBox(_selectedSceneNode->getTransformedBoundingBox())) {
			gGameInfo.setEnemyLife(gGameInfo.enemyLife()-10);
			if(gGameInfo.enemyLife() == 0)  {
				((MOB*)_selectedSceneNode)->die(timeScale);
				int x = gGameInfo.xp()+((MOB*)_selectedSceneNode)->xp();
				gGameInfo.setXP(x);
			}
		}

	}

	for(size_t i = 0; i < _mobs.size(); ++i) {
		if(_mobs[i]->isDead()) 
		{
			// deselect
			if(_selectedSceneNode == _mobs[i]) {
				_selectedSceneNode = NULL;
			}

			// remove from scene
			_sceneIrr->addToDeletionQueue(_mobs[i]);
			//_sceneIrr->addToDeletionQueue(_mobs[i]->billboardNode());
			
			// add body
			StaticObject *body = new StaticObject("../../Data/MOBs/AntDead.obj", _sceneIrr->getRootSceneNode(), _sceneIrr, ObjectType::OBJ_COLLECT);
			body->setPosition(_mobs[i]->getPosition());
			body->setScale(vector3df(5.0f, 3.0f, 3.0f));
			//body->setItems();
			_objs.push_back(body);

			_selector = _sceneIrr->createTriangleSelector(body->getMesh(), body);
			body->setTriangleSelector(_selector);
			_selector->drop();

			// erase char
			_mobs.erase(_mobs.begin()+i);
			--i;

			// hero stops attacking
			_hero->stop();
		}
		else {
			_mobs[i]->update(timeScale);
			core::vector3df position = _mobs[i]->getPosition();
			_terrain->getHeight(position);
			_mobs[i]->setPosition(position);
		}
	}

	_hero->update(timeScale);

	_hud.update();

	_changedSelection = false;

	//_water.update(timeScale);
}

void Game::draw()
{
	_sceneIrr->drawAll();
	_hud.draw();
}

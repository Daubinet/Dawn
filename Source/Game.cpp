#include "Globals.h"
#include "Game.h"

Game::Game(void)
{
	

}

Game::~Game(void)
{
}


void Game::initialize(Ogre::SceneManager *sceneManager, Ogre::Camera *camera, EventManager *handler)
{
	_handler = handler;
	_sceneManager = sceneManager;
	_camera = camera;
	
	_sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	
	//Loading and adding demo model to screen
	Ogre::SceneNode* _ninjanode = _sceneManager->getRootSceneNode()->createChildSceneNode("Ninja");
	_ninjanode->setPosition( 0, 1, 750);
	_ninja = new StaticObject("Ninja", _sceneManager->createEntity("Ninja","Ninja.mesh"), _ninjanode);
	_ninjanode->attachObject(_ninja->getEntity());



	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* entGround = _sceneManager->createEntity("GroundEntity", "ground"); 
	_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);

	entGround->setMaterialName("Examples/Rockwall"); 
	entGround->setCastShadows(false);

	// set its position, direction  
	_camera->setPosition(Ogre::Vector3(0,100,500)); 
	_camera->lookAt(Ogre::Vector3(0,0,0));

	// set the near clip distance 
	_camera->setNearClipDistance(5);  
}

void Game::update()
{
	// If the mesh exists 
	if(_ninja != NULL){
	Ogre::Real X =_ninja->position().x;
	Ogre::Real Z =_ninja->position().z;
	Ogre::Real Y =_ninja->position().y;

	if(_handler->pressedKey(OIS::KC_ESCAPE))
		gQuit = true;

	if(_handler->isPressingKey(OIS::KC_UP))
		 Z += 0.5;
	if(_handler->isPressingKey(OIS::KC_DOWN))
		Z -= 0.5;
	if(_handler->isPressingKey(OIS::KC_LEFT))
		 X -= 0.5;
	if(_handler->isPressingKey(OIS::KC_RIGHT))
		 X +=0.5;
	
	
		_ninja->setPosition( X, Y, Z);
	
	}
}

void Game::draw()
{
	_ninja->position();
}


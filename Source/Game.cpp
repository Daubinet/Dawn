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

	Ogre::Entity* entNinja = _sceneManager->createEntity("Ninja", "ninja.mesh"); 
	entNinja->setCastShadows(true); 
	_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);

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
	if(_handler->pressedKey(OIS::KC_ESCAPE))
		gQuit = true;


}

void Game::draw()
{
}


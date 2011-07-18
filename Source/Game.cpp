#include "Globals.h"
#include "Game.h"

Game::Game(void)
{
	

}

Game::~Game(void)
{
}

void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img) 
{
	img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	if (flipX) img.flipAroundY(); if (flipY) img.flipAroundX();  
}

void Game::initialize(Ogre::SceneManager *sceneManager, Ogre::Camera *camera, EventManager *handler)
{
	_handler = handler;
	_sceneManager = sceneManager;
	_camera = camera;
	
	_sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	
	// Loading and adding demo model to screen
	Ogre::SceneNode* _ninjanode = _sceneManager->getRootSceneNode()->createChildSceneNode("Ninja");
	_ninjanode->setPosition(Ogre::Vector3(1683, 50, 2110));
		
	_ninja = new StaticObject("Ninja", _sceneManager->createEntity("Ninja","WereVixen.mesh"), _ninjanode);
	_ninjanode->attachObject(_ninja->getEntity());
	_ninjanode->scale(10, 10, 10);


	Ogre::Vector3 lightdir(0.55, -0.3, 0.75); lightdir.normalise();  
	Ogre::Light* light = _sceneManager->createLight("tstLight"); 
	light->setType(Ogre::Light::LT_DIRECTIONAL); 
	light->setDirection(lightdir); 
	light->setDiffuseColour(Ogre::ColourValue::White); 
	light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));  
	_sceneManager->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));

	mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions(); 
	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(_sceneManager, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f); 
	mTerrainGroup->setFilenameConvention(Ogre::String("BasicTutorial3Terrain"), Ogre::String("dat"));
	mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);  
	configureTerrainDefaults(light); 

	for (long x = 0; x <= 0; ++x) 
		for (long y = 0; y <= 0; ++y) 
			defineTerrain(x, y); 

	// sync load since we want everything in place when we start 
	mTerrainGroup->loadAllTerrains(true);
	if (mTerrainsImported) { 
		Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
		while(ti.hasMoreElements()) { 
			Ogre::Terrain* t = ti.getNext()->instance; 
			initBlendMaps(t);
		}
	}
	mTerrainGroup->freeTemporaryResources();  

	// skybox
	Ogre::Plane skybox;
	skybox.d = 100; 
	skybox.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;  
	_sceneManager->setSkyPlane(true, skybox, "Examples/CloudySky", 500, 20, true, 0.5, 150, 150); 

	// set camera
	_camera->setPosition(_ninja->position()+Ogre::Vector3(0, 10, 100)); 
	_camera->lookAt(_ninja->position());
	_camera->setNearClipDistance(5);  
	_camera->setFarClipDistance(0);
}


void Game::defineTerrain(long x, long y) 
{
	Ogre::String filename = mTerrainGroup->generateFilename(x, y);
	if(Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
	{
		mTerrainGroup->defineTerrain(x, y);
	} 
	else 
	{ 
		Ogre::Image img; getTerrainImage(x % 2 != 0, y % 2 != 0, img);
		mTerrainGroup->defineTerrain(x, y, &img);
		mTerrainsImported = true; 
	} 
} 

void Game::initBlendMaps(Ogre::Terrain* terrain) 
{
	Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
	Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
	Ogre::Real minHeight0 = 70;
	Ogre::Real fadeDist0 = 40;
	Ogre::Real minHeight1 = 70;
	Ogre::Real fadeDist1 = 15;

	float* pBlend1 = blendMap1->getBlendPointer();
	for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y) 
	{ 
		for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x) 
		{ 
			Ogre::Real tx, ty;  
			blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
			Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
			Ogre::Real val = (height - minHeight0) / fadeDist0; 
			val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);  
			val = (height - minHeight1) / fadeDist1;
			val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1); *pBlend1++ = val; 
		} 
	} 
	
	blendMap0->dirty(); 
	blendMap1->dirty(); 
	blendMap0->update(); 
	blendMap1->update(); 
}

void Game::configureTerrainDefaults(Ogre::Light* light) 
{ 
	// Configure global 
	mTerrainGlobals->setMaxPixelError(8); 
	// testing composite map 
	mTerrainGlobals->setCompositeMapDistance(3000);  
	// Important to set these so that the terrain knows what to use for derived (non-realtime) data 
	mTerrainGlobals->setLightMapDirection(light->getDerivedDirection()); 
	mTerrainGlobals->setCompositeMapAmbient(_sceneManager->getAmbientLight());
	mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());  
	// Configure default import settings for if we use imported image 
	Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings(); 
	defaultimp.terrainSize = 513; 
	defaultimp.worldSize = 12000.0f; 
	defaultimp.inputScale = 600; 
	defaultimp.minBatchSize = 33; 
	defaultimp.maxBatchSize = 65; 
	// textures 
	defaultimp.layerList.resize(3); 
	defaultimp.layerList[0].worldSize = 100; 
	defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds"); 
	defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds"); 
	defaultimp.layerList[1].worldSize = 30; 
	defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds"); 
	defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds"); 
	defaultimp.layerList[2].worldSize = 200; defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds"); 
	defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds"); 
} 

void Game::update(unsigned long milliseconds)
{
	double seconds = milliseconds/1000.0;

	Ogre::Real X =_ninja->position().x;
	Ogre::Real Z =_ninja->position().z;
	Ogre::Real Y =_ninja->position().y;


	if(_handler->pressedKey(OIS::KC_ESCAPE))
		gQuit = true;

	if(_handler->isPressingKey(OIS::KC_UP))
		Z += 15*seconds;
	if(_handler->isPressingKey(OIS::KC_DOWN))
		Z -= 15*seconds;
	if(_handler->isPressingKey(OIS::KC_LEFT))
		X -= 15*seconds;
	if(_handler->isPressingKey(OIS::KC_RIGHT))
		X += 15*seconds;
	
	_ninja->setPosition(X, Y, Z);
	_camera->setPosition(_ninja->position()+Ogre::Vector3(0, 10, 100)); 
	_camera->lookAt(_ninja->position());

}

void Game::draw()
{
	_ninja->position();
}


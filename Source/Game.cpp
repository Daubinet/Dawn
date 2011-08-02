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

void Game::initialize(Ogre::Camera *camera, EventManager *handler)
{
	_handler = handler;
	_camera = camera;
	
	gSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	gSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	
	Ogre::Vector3 lightdir(0.55, -0.3, 0.75); lightdir.normalise();  
	Ogre::Light* light = gSceneManager->createLight("tstLight"); 
	light->setType(Ogre::Light::LT_DIRECTIONAL); 
	light->setDirection(lightdir); 
	light->setDiffuseColour(Ogre::ColourValue::White); 
	light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
	gSceneManager->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));

	mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions(); 
	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(gSceneManager, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f); 
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

	_werewolf.create("Werewolf");
	_werewolf.setMesh("Werewolf", "WereVixen.mesh");
	_werewolf.setPosition(Ogre::Vector3(1693, 20, 2090));
	_werewolf.setScale(Ogre::Vector3(5, 5, 5));
	_werewolf.setRotation(Ogre::Radian(1.57), Ogre::Radian(0), Ogre::Radian(3.14));

	_monster.create("Mobbie");
	_monster.setMesh("Mobbie", "WereVixen.mesh");
	_monster.setPosition(Ogre::Vector3(1708, 20, 2005));
	_monster.setScale(Ogre::Vector3(5, 5, 5));
	_monster.setRotation(Ogre::Radian(1.57), Ogre::Radian(0), Ogre::Radian(3.14));
	
	_streetLamp.create("StreetLamp");
	_streetLamp.setMesh("StreetLamp", "StreetLamp1.mesh");
	_streetLamp.setPosition(Ogre::Vector3(1703, mTerrainGroup->getHeightAtWorldPosition(Ogre::Vector3(1703, 0, 1110)), 1110));
	_streetLamp.setScale(Ogre::Vector3(2.5, 2.5, 2.5));
	_streetLamp.setRotation(Ogre::Radian(0), Ogre::Radian(1.57), Ogre::Radian(0));

	_sellingHouse.create("SellingHouse");
	_sellingHouse.setMesh("SellingHouse", "SellingHouse.mesh");
	_sellingHouse.setPosition(Ogre::Vector3(1803,mTerrainGroup->getHeightAtWorldPosition(Ogre::Vector3(1903, 0, 1870)), 1570));
	_sellingHouse.setScale(Ogre::Vector3(2.0, 2.0, 2.0));

	Ogre::Plane skybox;
	skybox.d = 100; 
	skybox.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;  
	gSceneManager->setSkyPlane(true, skybox, "Examples/CloudySky", 500, 20, true, 0.5, 150, 150); 

	// set camera
	_camera->setPosition(_werewolf.position()+Ogre::Vector3(0, 10, 100)); 
	_camera->lookAt(_werewolf.position());
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
	mTerrainGlobals->setCompositeMapAmbient(gSceneManager->getAmbientLight());
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

	if(_handler->pressedKey(OIS::KC_ESCAPE))
		gQuit = true;

	if(_handler->isPressingKey(OIS::KC_UP))
		_werewolf.walk();

	if(_handler->isPressingKey(OIS::KC_D))
		_monster.setHealth(-100);

	if(_monster.health() <= 0)
		_monster.die();

	// calculate monster movement
	_monster.updateAI(seconds);
		
	// update
	_werewolf.update(seconds);
	_monster.update(seconds);

	// fix heights
	Ogre::Real Y = mTerrainGroup->getHeightAtWorldPosition(_werewolf.position());
	_werewolf.setY(Y);
	Y = mTerrainGroup->getHeightAtWorldPosition(_monster.position());
	_monster.setY(Y);
	
	// set camera
	_camera->setPosition(_werewolf.position()+Ogre::Vector3(0, 30, 50)); 
	_camera->lookAt(_werewolf.position()+Ogre::Vector3(0, 20, 0));
	
}


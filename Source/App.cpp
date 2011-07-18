#include <Ogre.h>
#include <OgreWindowEventUtilities.h>
#include "EventManager.h"
#include "App.h"
#include "Globals.h"

App::App()
{
}

App::~App()
{
	delete handler;
	delete ogre;
}

void App::initialize()
{
	ogre = new Ogre::Root();

	// load common plugins
#ifdef _DEBUG
	ogre->loadPlugin("RenderSystem_Direct3D9_d");		
	ogre->loadPlugin("RenderSystem_GL_d");		
	ogre->loadPlugin("Plugin_ParticleFX_d");		
	ogre->loadPlugin("Plugin_BSPSceneManager_d");		
	ogre->loadPlugin("Plugin_CgProgramManager_d");		
	ogre->loadPlugin("Plugin_PCZSceneManager_d");		
	ogre->loadPlugin("Plugin_OctreeZone_d");		
	ogre->loadPlugin("Plugin_OctreeSceneManager_d");			

#else
	ogre->loadPlugin("Plugin_CgProgramManager");		
	ogre->loadPlugin("Plugin_OctreeSceneManager");
#endif
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../Data/fonts", "FileSystem", "Popular");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../Data/materials/programs", "FileSystem", "Popular");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../Data/materials/scripts", "FileSystem", "Popular");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../Data/materials/textures", "FileSystem", "Popular");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../Data/materials/textures/nvidia", "FileSystem", "Popular");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../Data/models", "FileSystem", "Popular");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../Data/particle", "FileSystem", "Popular");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../Data/DeferredShadingMedia", "FileSystem", "Popular");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../Data/PCZAppMedia", "FileSystem", "Popular");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../Data/RTShaderLib", "FileSystem", "Popular");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../Data/RTShaderLib/materials", "FileSystem", "Popular");
	
	Ogre::RenderSystemList renderSystems;
	Ogre::RenderSystemList::iterator r_it;
	renderSystems = ogre->getAvailableRenderers();
	r_it = renderSystems.begin();
	ogre->setRenderSystem(*r_it);
	ogre->initialise(false);

	// setup main window; hardcode some defaults for the sake of presentation
	Ogre::NameValuePairList opts;
	opts["resolution"] = "1024x768";
	opts["fullscreen"] = "false";
	opts["vsync"] = "false";

	// create a rendering window with the title "CDK"
	window = ogre->createRenderWindow("Dawn of the Wolf", 1024, 768, false, &opts);

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// since this is basically a CEGUI app, we can use the ST_GENERIC scene manager for now; in a later article 
	// we'll see how to change this
	sceneMgr = ogre->createSceneManager(Ogre::ST_GENERIC);
	camera = sceneMgr->createCamera("camera");
    Ogre::Viewport* vp = window->addViewport(camera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

	// most examples get the viewport size to calculate this; for now, we'll just 
	// set it to 4:3 the easy way
	camera->setAspectRatio((Ogre::Real)1.333333);

	// this next bit is for the sake of the input handler
	unsigned long hWnd;
	window->getCustomAttribute("WINDOW", &hWnd);

	handler = new EventManager(hWnd);

	game.initialize(sceneMgr, camera, handler);
}
void App::destroyWindow()
{
	if(sceneMgr != NULL){
		sceneMgr->destroyAllCameras();
		sceneMgr->destroyAllEntities();
		sceneMgr->destroyAllParticleSystems();
		sceneMgr->destroyAllLights();
		sceneMgr->destroyAllManualObjects();
		sceneMgr->destroyAllAnimations();
		sceneMgr->destroyAllMovableObjects();
	}

	if(window != NULL)
		window->destroy();
	if(ogre != NULL)
		ogre->destroyAllRenderQueueInvocationSequences();
	
}
void App::mainLoop()
{
	_timer.reset();
	gQuit = false;
	while(!gQuit) {
		// get events		
		handler->capture();

		// update
		game.update(_timer.getMilliseconds());
		_timer.reset();

		//draw
		game.draw();
		ogre->renderOneFrame();
	}
}


#if defined(WIN32)
#include <windows.h>
int APIENTRY WinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
#else
int main (int argc, char *argv[]) 
{
#endif
	App app;
	app.initialize();
	app.mainLoop();
	app.destroyWindow();
	return 0;
}

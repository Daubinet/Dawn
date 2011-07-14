 /*
App.cpp
*/

#include "App.h"
#include "Globals.h"
#include "SceneManager.h"
#include "Text.h"

using namespace irr;
using namespace core;
using namespace gui;
using namespace scene;
using namespace video;

App::App()
{
	device = NULL;
}

App::~App()
{
	device->drop();
}

void App::exit()
{
    device->closeDevice();
}

bool App::initialize()
{
	screenWidth = 1024;
	screenHeight = 768;

	// create device
	device = createDevice(video::EDT_DIRECT3D9, core::dimension2d<u32>(screenWidth, screenHeight), 16, false, true, false, &eventReceiver);
	if(device == NULL)
		return false;
	device->getCursorControl()->setVisible(false);

	render = device->getVideoDriver();
	if(render == NULL)
		return false;
	timer = device->getTimer();
	if(timer == NULL)
		return false;

	//device->setWindowCaption(L"RPG v0.1");

	// initialize globals
	//database.connect();
	text.initialize();

	return sceneManager.initialize();
}

void App::run()
{

	int lastFPS = -1;
	//the "last" time
	u32 timeStamp = timer->getTime();
	while(device->run())
	{	
        const u32 current = timer->getTime();
         const f32 deltaTime = (current - timeStamp) / 1000.f; // Time in seconds
        timeStamp = current;

		eventReceiver.update();

		sceneManager.handleEvents(deltaTime);
		sceneManager.update(deltaTime);
		sceneManager.draw();

		int fps = render->getFPS();
        if (lastFPS != fps)
        {
                stringw tmp(L"Project Squirmish v0.1 -");
                tmp += L" fps: ";
                tmp += fps;
                device->setWindowCaption(tmp.c_str());
                lastFPS = fps;
        }
	}
}

int main()
{
	App client;
	if(!client.initialize())
		return -1;

	client.run();
	return 0;
}


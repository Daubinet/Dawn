 /*
Client.cpp
*/

#include "Client.h"
#include "Globals.h"
#include "SceneManager.h"
#include "Text.h"

using namespace irr;
using namespace core;
using namespace gui;
using namespace scene;
using namespace video;

Client::Client()
{
	gDevice = NULL;
}

Client::~Client()
{
	gDevice->drop();
}

void Client::exit()
{
    gDevice->closeDevice();
}

bool Client::initialize()
{
	gScreenWidth = 1024;
	gScreenHeight = 768;

	// create gDevice
	gDevice = createDevice(video::EDT_DIRECT3D9, core::dimension2d<u32>(gScreenWidth, gScreenHeight), 16, false, true, false, &gEventReceiver);
	if(gDevice == NULL)
		return false;
	gDevice->getCursorControl()->setVisible(false);

	gRender = gDevice->getVideoDriver();
	if(gRender == NULL)
		return false;
	gTimer = gDevice->getTimer();
	if(gTimer == NULL)
		return false;

	// initialize globals
	gText.initialize();
	return gSceneManager.initialize();
}

void Client::run()
{

	int lastFPS = -1;
	//the "last" time
	u32 timeStamp = gTimer->getTime();
	while(gDevice->run())
	{	
        const u32 current = gTimer->getTime();
		// Time in seconds
        const f32 deltaTime = (current - timeStamp) / 1000.f;
        timeStamp = current;

		gEventReceiver.update();

		gSceneManager.handleEvents(deltaTime);
		gSceneManager.update(deltaTime);
		gSceneManager.draw();

		int fps = gRender->getFPS();
        if (lastFPS != fps)
        {
            stringw tmp(L"Project Squirmish v0.1 -");
            tmp += L" fps: ";
            tmp += fps;
            gDevice->setWindowCaption(tmp.c_str());
            lastFPS = fps;
        }
	}
}

int main()
{
	Client client;
	if(!client.initialize())
		return -1;

	client.run();
	return 0;
}


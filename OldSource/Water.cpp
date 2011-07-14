#include <fstream>
#include <string>
#include <irrlicht.h>
#include "Globals.h"
#include "SceneManager.h"
#include "Water.h"

using namespace core;

Water::Water()
{
}

Water::~Water()
{
}

void Water::initialize(ISceneManager *sceneIrr)
{
	mesh = sceneIrr->addHillPlaneMesh("water", core::dimension2d<f32>(20,20), core::dimension2d<u32>(40,40), 0, 0, core::dimension2d<f32>(0,0), core::dimension2d<f32>(10,10));
	node = sceneIrr->addWaterSurfaceSceneNode(mesh->getMesh(0), 0.1f, 1000.0f, 0.1f);

	node->setMaterialTexture(0, gRender->getTexture("../../Data/Textures/dirt.bmp"));
	node->setMaterialTexture(1, gRender->getTexture("../../Data/Textures/water.jpg"));

	node->setMaterialType(video::EMT_REFLECTION_2_LAYER);
}

void Water::update(f32 timeScale)
{
	static float time = 0.0;
	time += timeScale;

	node->setPosition(core::vector3df(0,(sin(time)+1.0),0));

	if(time > 6.2831853) time -= 6.2831853;
}

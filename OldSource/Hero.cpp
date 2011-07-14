#include "Globals.h"
#include "Hero.h"

Hero::Hero(std::string filename, std::string filename2, scene::ISceneNode* parent, scene::ISceneManager* sceneIrr, s32 id)
: Char(filename, filename2, parent, sceneIrr, id)
{
}

Hero::~Hero()
{
}

void Hero::update(f32 timeScale)
{
	Char::update(timeScale);

	_stats->setPosition(getPosition());
	_stats->setRotation(getRotation());
}

void Hero::render()
{
	CAnimatedMeshSceneNode::render();

	video::SMaterial debug_mat;
	debug_mat.Lighting = false;
	debug_mat.AntiAliasing=0;
	gRender->setMaterial(debug_mat);

	gRender->setTransform(ETS_WORLD, IdentityMatrix);
	gRender->draw3DBox(getTransformedBoundingBox(), video::SColor(255,0,255,0));
	gRender->draw3DBox(getAttackArea(), video::SColor(255,255,0,0));
}

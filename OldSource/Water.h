#ifndef __WATER_H
#define __WATER_H

#include <irrlicht.h>

using namespace irr;

class Water
{
public:
	Water();
	~Water();

	void initialize(ISceneManager *sceneIrr);
	void update(f32 timeScale);

private:
	scene::ISceneNode *node;
	scene::IAnimatedMesh *mesh;
};


#endif // __WATER_H
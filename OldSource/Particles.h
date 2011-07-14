#ifndef __PARTICLES_H
#define __PARTICLES_H

#include <irrlicht.h>
using namespace irr;
using namespace scene;

class Particles
{
public:
	Particles();

	// Set type of particle
	void setFire(ISceneManager *sceneIrr);

	// Sets
	void setPosition(core::vector3df position);

private:
	scene::IParticleSystemSceneNode *_ps;

};


#endif // __PARTICLES_H
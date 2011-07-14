#include "Particles.h"
#include "Globals.h"

Particles::Particles()
{
}

void Particles::setFire(ISceneManager *sceneIrr)
{
	_ps = sceneIrr->addParticleSystemSceneNode(false);

	scene::IParticleEmitter* em = _ps->createBoxEmitter(
		core::aabbox3d<f32>(-0.1,0,-0.1,0.1,0.1,0.1), // emitter size
		core::vector3df(0.0f,0.06f,0.0f),   // initial direction
		100,100,                             // emit rate
		video::SColor(0,255,0,0),       // darkest color
		video::SColor(0,255,255,0),       // brightest color
		50,300,10,                         // min and max age, angle
		core::dimension2df(3.f,3.f),         // min size
		core::dimension2df(8.f,8.f));        // max size

	_ps->setEmitter(em); // this grabs the emitter
	em->drop(); // so we can drop it here without deleting it

	scene::IParticleAffector* paf = _ps->createFadeOutParticleAffector(video::SColor(0,0,0,0), 10);

	_ps->addAffector(paf); // same goes for the affector
	paf->drop();

	_ps->setScale(core::vector3df(0.1,0.1,1));
	_ps->setMaterialFlag(video::EMF_LIGHTING, false);
	_ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	_ps->setMaterialTexture(0, gRender->getTexture("../../Data/Textures/fire.bmp"));
	_ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
}

void Particles::setPosition(core::vector3df position)
{
	_ps->setPosition(position);
}
#include "ActionType.h"
#include "AnimatedObject.h"
#include "Globals.h"

AnimatedObject::AnimatedObject()
: _node(NULL), _mesh(NULL), _anim(NULL)
{
}

AnimatedObject::~AnimatedObject()
{
}
	
void AnimatedObject::create(std::string name)
{
	if(_node)
		delete _node;
	_node = gSceneManager->getRootSceneNode()->createChildSceneNode(name);
}

void AnimatedObject::setMesh(std::string name, std::string file)
{
	if(_mesh)
		delete _mesh;

	_mesh = gSceneManager->createEntity(name, file);
	_node->attachObject(_mesh);
	_anim = _mesh->getAnimationState("Idle");
}

void AnimatedObject::update(double seconds)
{
	if(_anim) 
		_anim->addTime(seconds);
}

void AnimatedObject::setAnimation(Ogre::AnimationState *anim, bool loop)
{
	if(_anim) {
		_anim->setEnabled(false);
		_anim->setTimePosition(0);
	}
	_anim = anim;
	_anim->setEnabled(true);
	_anim->setLoop(loop);
}

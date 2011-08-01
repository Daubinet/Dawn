#include "AnimatedObject.h"
#include "Globals.h"

AnimatedObject::AnimatedObject()
: _node(NULL), _mesh(NULL), _anim(NULL), _idleSinceUpdate(true)
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

	_idle = _mesh->getAnimationState("Idle");
	_walk = _mesh->getAnimationState("Walk");
}

void AnimatedObject::idle()
{
	if(_actionType == ANIM_IDLE)
		return;

	_actionType = ANIM_IDLE;
	if(_anim) {
		_anim->setEnabled(false);
		_anim->setTimePosition(0);
	}
	_anim = _idle;
	_anim->setEnabled(true);
}

void AnimatedObject::walk()
{
	_idleSinceUpdate = false;

	if(_actionType == ANIM_WALK)
		return;

	_actionType = ANIM_WALK;
	if(_anim) {
		_anim->setEnabled(false);
		_anim->setTimePosition(0);
	}
	_anim = _walk;
	_anim->setEnabled(true);
}

void AnimatedObject::update(double seconds)
{
	if(_idleSinceUpdate) {
		idle();
	}
	else {
		switch(_actionType)
		{
		case ANIM_WALK:
			Ogre::Vector3 pos = position();
			setPosition(Ogre::Vector3(pos.x, pos.y, pos.z-10*seconds));
			break;
		}
	}

	if(_anim) 
		_anim->addTime(seconds);

	_idleSinceUpdate=true;
}

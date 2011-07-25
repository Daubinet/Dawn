#include "AnimatedObject.h"
#include "Globals.h"

AnimatedObject::AnimatedObject()
: _node(NULL), _mesh(NULL), _anim(NULL)
{
}

AnimatedObject::~AnimatedObject()
{
}
	
void AnimatedObject::update(double seconds)
{
	if(_anim == NULL)
		return;

	_anim->addTime(seconds);
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
}

void AnimatedObject::animate(std::string animName)
{
	_anim = _mesh->getAnimationState(animName);
	_anim->setLoop(true); 
	_anim->setEnabled(true); 
}
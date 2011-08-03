#include "ActionType.h"
#include "AnimatedObject.h"
#include "Globals.h"

AnimatedObject::AnimatedObject()
: _node(NULL), _mesh(NULL), _actionType(Action::ACT_IDLE), _idleSinceUpdate(true)
{
	for(int i = 0; i < Action::ACT_NUM; ++i)
		_anim[i] = NULL;
}

AnimatedObject::~AnimatedObject()
{
}

void AnimatedObject::setAction(Action::Type action)
{
	// not idle since last update
	if(action != Action::ACT_IDLE)
		_idleSinceUpdate = false;

	// if doesnt have animation or is already using it
	if(_actionType == action)
		return;
	if(!(_animations & Action::getFlag(action)))
		return;

	// clean old anim
	if(_anim[_actionType]) {
		_anim[_actionType]->setEnabled(false);
		_anim[_actionType]->setTimePosition(0);
	}
	
	_actionType = action;
	_anim[_actionType]->setEnabled(true);
}
	
void AnimatedObject::create(std::string name)
{
	if(_node)
		delete _node;
	_node = gSceneManager->getRootSceneNode()->createChildSceneNode(name);
}

void AnimatedObject::setMesh(std::string name, std::string file, unsigned long animations)
{
	if(_mesh)
		delete _mesh;

	_mesh = gSceneManager->createEntity(name, file);
	_node->attachObject(_mesh);
	
	_animations = animations;
	if(_animations & Action::getFlag(Action::ACT_IDLE))
		_anim[Action::ACT_IDLE] = _mesh->getAnimationState("Idle");
	if(_animations & Action::getFlag(Action::ACT_WALK))
		_anim[Action::ACT_WALK] = _mesh->getAnimationState("Walk");

	if(_animations & Action::getFlag(Action::ACT_DIE)) {
		_anim[Action::ACT_DIE] = _mesh->getAnimationState("Fall");
		_anim[Action::ACT_DIE]->setLoop(false);
	}
}

void AnimatedObject::update(double seconds)
{
	// info updates	
	if(_idleSinceUpdate)
		setAction(Action::ACT_IDLE);

	switch(_actionType)
	{
	case Action::ACT_WALK:
		Ogre::Vector3 pos = position();
		setPosition(Ogre::Vector3(pos.x, pos.y, pos.z-10*seconds));
		break;
	}

	// mesh/node updates
	if(_anim[_actionType]) 
		_anim[_actionType]->addTime(seconds);

	_idleSinceUpdate=true;
}

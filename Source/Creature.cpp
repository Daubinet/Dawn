#include "Globals.h"
#include "Creature.h"
#include "ActionType.h"

Creature::Creature() 
: _health(100), _idleSinceUpdate(true)
{
}

void Creature::setMesh(std::string name, std::string file)
{
	if(_mesh)
		delete _mesh;

	_mesh = gSceneManager->createEntity(name, file);
	_node->attachObject(_mesh);

	_idle = _mesh->getAnimationState("Idle");
	_walk = _mesh->getAnimationState("Walk");
	_die = _mesh->getAnimationState("Fall");
}

void Creature::idle()
{
	if(_actionType == Action::ACT_IDLE)
		return;
	_actionType = Action::ACT_IDLE;
	setAnimation(_idle);
}

void Creature::die()
{
	_idleSinceUpdate = false;
	if(_actionType == Action::ACT_DIE)
		return;
	_actionType = Action::ACT_DIE;
	setAnimation(_die, false);
}

void Creature::walk()
{
	_idleSinceUpdate = false;
	if(_actionType == Action::ACT_WALK)
		return;
	_actionType = Action::ACT_WALK;
	setAnimation(_walk);
}

void Creature::update(double seconds)
{
	// info updates
	switch(_actionType)
	{
	case Action::ACT_WALK:
		Ogre::Vector3 pos = position();
		setPosition(Ogre::Vector3(pos.x, pos.y, pos.z-10*seconds));
		break;
	}

	// mesh/node updates
	if(_idleSinceUpdate)
		idle();

	if(_anim) 
		_anim->addTime(seconds);

	_idleSinceUpdate=true;
}
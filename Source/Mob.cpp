#include "Mob.h"

Mob::Mob()
{
	_stats.health = 100;
	_basicAI.setStats(&_stats);
}

void Mob::setBehavior(BasicAI::Behavior behavior)
{
	_basicAI.setBehavior(behavior);
}

void Mob::updateAI(double seconds)
{
	_basicAI.getNextAction(&_actionType, &_actionModif);
	if(_actionType != Action::ACT_IDLE)
		_idleSinceUpdate = false;
}

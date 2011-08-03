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
	_actionType = _basicAI.getNextAction();
}

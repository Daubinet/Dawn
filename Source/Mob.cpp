#include "Mob.h"

Mob::Mob()
{
}

void Mob::setBehavior(BasicAI::Behavior behavior)
{
	_basicAI.setBehavior(behavior);
}

void Mob::updateAI(double seconds)
{
	_actionType = _basicAI.getNextAction();
}

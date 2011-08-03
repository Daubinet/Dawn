#include "BasicAI.h"

void BasicAI::setBehavior(BasicAI::Behavior behavior)
{
	_behavior = behavior;
}

Action::Type BasicAI::getNextAction()
{
	if(_stats->health < 0)
		return Action::ACT_DIE;
	
	switch(_behavior)
	{
	case AI_PATROLL:
		return Action::ACT_WALK;
		break;
	// should never happen
	default:
		return Action::ACT_WALK;
		break;
	}
}
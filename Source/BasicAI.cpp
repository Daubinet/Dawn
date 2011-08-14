#include "BasicAI.h"

void BasicAI::setBehavior(BasicAI::Behavior behavior)
{
	_behavior = behavior;
}

void BasicAI::getNextAction(Action::Type *act, Action::Modifier *mod)
{
	if(_stats->health < 0) {
		*act = Action::ACT_DIE;
		return;
	}
	
	switch(_behavior)
	{
	case AI_PATROLL:
		*act = Action::ACT_WALK;
		*mod = Action::MDF_FRONT;
		break;
	// should never happen
	default:
		*act = Action::ACT_WALK;
		*mod = Action::MDF_FRONT;
		break;
	}
}
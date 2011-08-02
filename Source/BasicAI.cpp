#include "BasicAI.h"

void BasicAI::setBehavior(BasicAI::Behavior behavior)
{
	_behavior = behavior;
}

Action::Type BasicAI::getNextAction()
{
	return Action::ACT_WALK;
}
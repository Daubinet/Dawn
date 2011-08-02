#ifndef __BASICAI_H
#define __BASICAI_H

#include <OgreMath.h>
#include "Creature.h"

class BasicAI
{
public:
	enum Behavior { AI_PATROLL };

	void setBehavior(BasicAI::Behavior behavior);
	Action::Type getNextAction();

private:
	Behavior _behavior;

};

#endif // __BASICAI_H
#ifndef __MOB_H
#define __MOB_H

#include "Creature.h"
#include "BasicAI.h"
#include "MobStats.h"

class Mob : public Creature
{
public:
	Mob();

	void updateAI(double seconds);
	
	void setBehavior(BasicAI::Behavior behavior);

private:
	BasicAI _basicAI;
};

#endif // __MOB_H
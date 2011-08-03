#ifndef __MOB_H
#define __MOB_H

#include "AnimatedObject.h"
#include "BasicAI.h"
#include "MobStats.h"

class Mob : public AnimatedObject
{
public:
	Mob();

	void updateAI(double seconds);
	void setBehavior(BasicAI::Behavior behavior);

	void setHealth(int health) { _stats.health = health; }

private:
	BasicAI _basicAI;
	MobStats _stats;
};

#endif // __MOB_H
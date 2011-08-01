#ifndef _MOB_H_
#define _MOB_H_

#include "Creature.h"
#include "BasicAI.h"

class Mob : public Creature, public BasicAI
{
public:
	Mob() {
	m_faction = WEREWOLF;
	
	};

	void MoveToTarget(Creature target);
};
#endif
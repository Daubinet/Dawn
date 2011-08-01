#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Creature.h"


class Player : public Creature
{
public:
	Player() {
	m_faction = HUMAN;
	setAnimatedState(IDLE);
	};
};

#endif
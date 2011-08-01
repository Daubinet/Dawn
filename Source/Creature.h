#ifndef _CREATURE_H_
#define _CREATURE_H_
/*

          ----------------                    --------------
          |   Creature   |                    |  Item      |
          |--------------|                    |------------|
          | Name         |                    | Name       |
          | Hp           |                    | Value      |
          | Abilities    |--------------------| Weight     |
          |--------------|                    --------------
          | Attack       |
          ----------------
                 ^
                 |
        ----------------------
        |                    |
----------------    ----------------
|  Hero        |    |  Monster     |
|--------------|    |--------------|
| Level        |    |              |
|--------------|    |--------------|
| KillMonster  |    | AttackAndDie |
| GrabTreasure |    | DropTreasure |
----------------    ----------------

SOULMENS CHEATSHEET

*/


#include <stdlib.h>
#include <string>

#include "AnimatedObject.h"



enum DeathState {
	DEATH = 0,
	ALIVE,

};
enum CreatureFaction 
{
	HUMAN =0,
	WEREWOLF,

};
enum CreatureAnimatedState  // STATES FOR CREATURE IF HES WALKING RUNINg OR JUST IDLE
{
	IDLE =0,
	WALK,
	RUN,
};

class Creature : public AnimatedObject{

public:

	Creature();


	/*
		STATES of the creature
	*/

int getHealth()
{
	return m_health;
}

void setHealth(int health)
{
	m_health = health;
}
void setState(DeathState state)
{
	m_state = state;
}
DeathState getState();

void onDeath();

CreatureFaction getFaction()
{
	return m_faction;
}


CreatureFaction getTargetFaction(Creature target);

void setAnimatedState(CreatureAnimatedState ani);

Ogre::Vector3 getDistance(Creature target);

//bool InRadius(Creature target);

void moveTo(Ogre::Vector3 v) {
setAnimatedState(WALK);
setPosition(v);
}
void getRotate(Creature target);

protected:

	std::string m_name;
	int m_health;
	DeathState m_state;
	CreatureFaction m_faction;
	
};

#endif
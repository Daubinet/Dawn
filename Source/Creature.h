#ifndef __CREATURE_H
#define __CREATURE_H
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

class Creature : public AnimatedObject
{
public:
	Creature();

	virtual void setMesh(std::string name, std::string file);

	void idle();
	void die();
	void walk();
	virtual void update(double seconds);

	// Stats
	int health() { return _health; }
	void setHealth(int health) { _health = health; }

protected:
	Ogre::AnimationState *_idle, *_walk, *_die;
	std::string _name;
	int _health;
	Action::Type _actionType;
	bool _idleSinceUpdate;
};

#endif
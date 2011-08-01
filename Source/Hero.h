#ifndef __HERO_H
#define __HERO_H

#include "AnimatedObject.h"

class Hero : public AnimatedObject
{
public:
	Hero();
	~Hero();

private:
	AnimationState *_run;

};

#endif // __HERO_H
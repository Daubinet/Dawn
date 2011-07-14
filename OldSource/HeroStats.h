/*
*/

#ifndef __HEROSTATS_H
#define __HEROSTATS_H

#include <string>
#include <vector>
#include <irrlicht.h>
#include "Stats.h"

using namespace irr;
using namespace core;

class HeroStats : public Stats
{
public:
	HeroStats();
	~HeroStats();

	// Sets
	void setXP(int xp) { _xp = xp; }
	void setGold(int gp ) { _gold = gp;}
	
	// Gets
	int xp() { return _xp; }
	int gold();

protected:
	int _xp;
	int _shield, _weapon, _gloves, _boots, _ring1, _ring2, _necklace;
	std::vector<int> _otherItems;
	int _gold;
};

#endif // __HEROSTATS_H
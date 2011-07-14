#include <fstream>
#include <string>
#include "HeroStats.h"

HeroStats::HeroStats()
{
	_health = 100;
	_gold =225;
}

HeroStats::~HeroStats()
{
}
int HeroStats::gold()
{
	if(_gold <= 0)
		return 0;

	return _gold;

}


#ifndef __REGION_H
#define __REGION_H

#include <string>
#include <vector>
#include "Stats.h"
#include "EnemyStats.h"

class Region
{
public:
	Region();
	~Region();

private:
	std::vector<EnemyStats> _mobs;
	std::vector<EnemyStats> _npcs;
	std::vector<Stats> _objs;
 };

#endif //__REGION_H
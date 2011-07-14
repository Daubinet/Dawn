#include <irrlicht.h> 
#include "EnemyStats.h"
#include "GameInfo.h"
#include "Globals.h"

using namespace irr;
using namespace core;
using namespace video;

GameInfo::GameInfo()
: _selectedEnemy(-1)
{
}

void GameInfo::loadRegion(int id)
{
	if(id == 0)
	{
		gGameInfo.addMob(0, 0, vector3df(150, 0, -100), vector3df(0, 180, 0));
		gGameInfo.addMob(1, 0, vector3df(130, 0, -50), vector3df(0, 90, 0));
		gGameInfo.addNpc(0, 1, vector3df(195, 0, -130), vector3df(0, 180, 0));
	}
}

// add enemies
EnemyStats *GameInfo::addMob(int id, int dbId, vector3df position, vector3df rotation)
{
	EnemyStats *stats = new EnemyStats();
	stats->setHealth(100);
	stats->setName("Giant Ant");
	stats->setIndex(id);
	stats->setDBId(dbId);
	stats->setPosition(position);
	_mobStats.push_back(stats);
	return stats;
}

EnemyStats *GameInfo::addNpc(int id, int dbId, vector3df position, vector3df rotation)
{
	EnemyStats *stats = new EnemyStats();
	stats->setHealth(100);
	stats->setName("Giant Ant");
	stats->setIndex(id);
	stats->setDBId(dbId);
	stats->setPosition(position);
	_npcStats.push_back(stats);
	return stats;
}

HeroStats *GameInfo::addHero(int id)
{
	if(_heroStats) 
		delete _heroStats;

	_heroStats = new HeroStats();
	_heroStats->setHealth(100);
	_heroStats->setPosition(vector3df(170, 10, -200));
	_heroStats->setRotation(vector3df(0, 0, 0));
	_heroStats->setName("Rosalia");
	_heroStats->setIndex(id);
	return _heroStats;
}

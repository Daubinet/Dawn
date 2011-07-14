#ifndef __GAMEINFO_H
#define __GAMEINFO_H

#include <irrlicht.h>
#include "Sprite2D.h"
#include "HeroStats.h"
#include "EnemyStats.h"
#include "Region.h"

using namespace irr;
using namespace video;

class GameInfo
{
public:
	GameInfo();

	// Load region
	void loadRegion(int id);
	HeroStats *addHero(int id);
	
	// Sets
	void setSelected(int id) { _selectedEnemy = id; }
	void setLife(int life) { _heroStats->setHealth(life); }
	void setXP(int xp) { _heroStats->setXP(xp); }
	void setEnemyLife(int life) { _mobStats[_selectedEnemy]->setHealth(life); }

	// Gets
	int life() { return _heroStats->health(); }
	int xp() { return _heroStats->xp(); }
	int nMobs() { return _mobStats.size(); }
	int nNpcs() { return _npcStats.size(); }
	EnemyStats *mobs(int i) { return _mobStats[i]; }
	EnemyStats *npcs(int i) { return _npcStats[i]; }

	int enemyLife() { 
		if(_selectedEnemy == -1) 
			return 0;
		else
			return _mobStats[_selectedEnemy]->health(); 
	}
	int enemyLife(int sel) { 
		return _mobStats[sel]->health(); 
	}
	vector3df heroPosition() { 
		return _heroStats->position(); 
	}
	HeroStats *hero() {
		return _heroStats;
	}
	
private:
	// Add chars
	EnemyStats *addMob(int id, int dbId, vector3df position, vector3df rotation);
	EnemyStats *addNpc(int id, int dbId, vector3df position, vector3df rotation);
	
	HeroStats *_heroStats;
	std::vector<EnemyStats*> _mobStats;
	std::vector<EnemyStats*> _npcStats;

	int _selectedEnemy;

	std::string _email;

	Region _region;
		
};

#endif // __GAMEINFO_H
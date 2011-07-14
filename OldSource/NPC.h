#ifndef __NPC_H
#define __NPC_H

#include "Char.h"
#include "EnemyStats.h"

class NPC : public Char
{
public:
	NPC(std::string filename, std::string filename2, scene::ISceneNode* parent, scene::ISceneManager* sceneIrr, s32 id);
	~NPC();

	void setStats(EnemyStats *stats) { 
		_stats = stats; 
		setPosition(stats->position());
		setRotation(stats->rotation());
	}

	int index() { return _stats->index(); }
	int xp() { return 50; }
	
private:
	EnemyStats *_stats;
};

#endif // __NPC_H

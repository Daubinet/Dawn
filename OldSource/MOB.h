#ifndef __MOB_H
#define __MOB_H

#include "AI.h"
#include "Char.h"
#include "EnemyStats.h"

class MOB : public Char
{
public:
	// Create/destroy
	MOB(std::string filename, std::string filename2, scene::ISceneNode* parent, scene::ISceneManager* sceneIrr, s32 id);
	~MOB();

	// Set behavior
	void patrollArea(int centerX, int centerY, int radius);
	void attack(int centerX, int centerY);

	void update(f32);

	// Sets
	void setStats(EnemyStats *stats) { 
		_stats = stats; 
		setPosition(stats->position());
		setRotation(stats->rotation());
	}

	// Gets
	int index() { return _stats->index(); }
	int xp() { return 50; }

	// Override
	virtual void render();

private:
	AI _ai;
	EnemyStats *_stats;
};

#endif // __MOB_H
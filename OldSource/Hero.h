#ifndef __HERO_H
#define __HERO_H

#include "Char.h"
#include "HeroStats.h"

class Hero : public Char
{
public:
	Hero(std::string filename, std::string filename2, scene::ISceneNode* parent, scene::ISceneManager* sceneIrr, s32 id);
	~Hero();

	//void setNode(ISceneManager *sceneIrr, std::string filename, std::string filename2);
	void setStats(HeroStats *stats) { _stats = stats; }

	// Actions
	virtual void update(f32 timeScale);
	virtual void render();

private:
	HeroStats *_stats;

};

#endif // __HERO_H
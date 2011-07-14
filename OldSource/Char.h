#ifndef __CHAR_H
#define __CHAR_H

#include <string>
#include "AnimObject.h"

class Char : public AnimObject
{
public:
	enum AnimationType
	{
		ANIM_Stand, ANIM_Walk, ANIM_Attack, ANIM_Die, ANIM_Total, ANIM_None
	};

	// Create/destroy
	Char(std::string filename, std::string filename2, scene::ISceneNode* parent, scene::ISceneManager* sceneIrr, s32 id);
	~Char();

	// Load
	void loadAnimInfo(std::string filename);

	// Attack area
	core::aabbox3d<f32> getAttackArea();

	// Move/rotation speed of a character
	void setMoveSpeed(float);
	void setRotSpeed(float);
	float getMoveSpeed();
	float getRotSpeed();

	// Gets
	bool isAttacking() const { return _isAttacking; }
	bool attacked() const { return _attackReady; }
	bool isDying() const { return _isDying; }
	bool isDead() const { return _isDead; }
	
	// Actions
	virtual void update(f32 timeScale);
	void attack(f32 timescale);
	void turnLeft(f32);
	void turnRight(f32);
	void walk(f32);
	void die(f32);
	void stop();
	
protected:
	AnimationType _currentAnimation;
	std::pair<int, int> _animInfo[ANIM_Total];
	int _animSpeed[ANIM_Total];
	float m_moveSpeed,m_rotSpeed;

	int _life;
	bool _isAttacking, _attackReady;
	float _attackTime;

	bool _isDying, _isDead;
	float _deathTime;
};

#endif // __CHAR_H
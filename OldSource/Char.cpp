#include <fstream>
#include "Char.h"
#include "Globals.h"
#include "Constants.h"
#include "SceneManager.h"

Char::Char(std::string filename, std::string filename2, scene::ISceneNode* parent, scene::ISceneManager* sceneIrr, s32 id)
: AnimObject(filename, filename2, parent, sceneIrr, id)
, _currentAnimation(ANIM_None)
, _life(100)
, _isAttacking(false)
, _attackReady(false)
, _isDying(false)
, _isDead(false)
{

	
}

Char::~Char()
{
}

void Char::setRotSpeed(float p_rotSpeed)
{
	m_rotSpeed = p_rotSpeed;
}
void Char::setMoveSpeed(float p_moveSpeed)
{
	m_moveSpeed = p_moveSpeed;
}
float Char::getMoveSpeed()
{
	return m_moveSpeed*FRAMES_PER_SECOND;
}
float Char::getRotSpeed()
{
	return m_rotSpeed*FRAMES_PER_SECOND;
}
void Char::loadAnimInfo(std::string filename)
{
	std::ifstream file(filename.c_str());
	for(int i = 0; i < ANIM_Total; ++i)
	{
		std::string comment;
		file >> _animInfo[i].first >> _animInfo[i].second >> _animSpeed[i] >> comment; 
	}

}

void Char::turnLeft(f32 timeScale)
{
	setRotation(getRotation() - vector3df(0.0f,((getRotSpeed()*timeScale)), 0.0f));
	_isAttacking = false;
}

void Char::turnRight(f32 timeScale)
{
	setRotation(getRotation() + vector3df(0.0f, ((getRotSpeed()*timeScale)), 0.0f));
	_isAttacking = false;
} 

void Char::walk(f32 timeScale)
{ 
	float magnitude = ((getMoveSpeed()*timeScale));
	vector3df offset = getDirection() * magnitude;

	setPosition(getPosition() + offset);
	_billboard->setPosition(getPosition()+vector3df(0, 15, 0)); 

	if(_currentAnimation != ANIM_Walk) {
		_currentAnimation = ANIM_Walk;
		setFrameLoop(_animInfo[ANIM_Walk].first, _animInfo[ANIM_Walk].second);
		setAnimationSpeed(_animSpeed[ANIM_Walk]);
	}
	_isAttacking = false;
}

void Char::stop()
{
	if(_currentAnimation != ANIM_Stand) {
		_currentAnimation = ANIM_Stand;
		setFrameLoop(_animInfo[ANIM_Stand].first, _animInfo[ANIM_Stand].second);
		setAnimationSpeed(_animSpeed[ANIM_Stand]);
	}
	_isAttacking = false;
}

void Char::die(f32 timeScale)
{
	if(_currentAnimation != ANIM_Die) {
		_currentAnimation = ANIM_Die;
		setFrameLoop(_animInfo[ANIM_Die].first, _animInfo[ANIM_Die].second);
		setAnimationSpeed(_animSpeed[ANIM_Die]);
	}
	_isAttacking = false;
	_isDying = true;
}


core::aabbox3d<f32> Char::getAttackArea()
{
	core::aabbox3d<f32> box = getTransformedBoundingBox();
	
	core::vector3df s = box.getExtent();

	box.MinEdge += s*getDirection();
	box.MaxEdge += s*getDirection();

	return box;
}

void Char::attack(f32 timeScale)
{
	if(_currentAnimation != ANIM_Attack) {
		_currentAnimation = ANIM_Attack;
		setFrameLoop(_animInfo[ANIM_Attack].first, _animInfo[ANIM_Attack].second);
		setAnimationSpeed(_animSpeed[ANIM_Attack]);
	}
	_isAttacking = true;
}

void Char::update(f32 timeScale)
{
	if(_isDead) {
		return;
	}

	// Attack
	_attackReady = false;
	if(_isAttacking)
	{
		_attackTime += timeScale;
		if(_attackTime > 1.0) {
			_attackTime -= 1.0;
			_attackReady = true;
		}
	}
	else
		_attackTime = 0.0;

	// Death
	if(_isDying) {
		_deathTime += timeScale;
		if(_deathTime > 1.0) {
			_isDying = false;
			_isDead = true;
			_deathTime = 0.0;
		}
	}
	else
		_deathTime = 0.0;
}
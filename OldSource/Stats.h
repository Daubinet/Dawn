#ifndef __STATS_H
#define __STATS_H

#include <string>
#include <irrlicht.h>

using namespace irr;
using namespace core;

class Stats
{
public:
	Stats();
	~Stats();

	std::string toString();

	// Sets
	void setHealth(int health) { _health = health; }
	void setName(std::string name) { _name = name; }
	void setPosition(vector3df position) { _position = position; }
	void setRotation(vector3df rotation) { _rotation = rotation; }
	
	// Gets
	int health() { return _health; }
	std::string name() { return _name; }
	vector3df position() { return _position; }
	vector3df rotation() { return _rotation; }
	bool isDead() { return _health <= 0; }
	
	// Index in current game info
	void setIndex(int index) { _index = index; }
	int index() { return _index; }

	// For database access
	void setDBId(int dbId) { _dbId = dbId; }
	int dbId() { return _dbId; }

protected:
	int _index;
	int _dbId;

	std::string _name;
	int _level;
	int _health;

	vector3df _position;
	vector3df _rotation;
};

#endif // __STATS_H
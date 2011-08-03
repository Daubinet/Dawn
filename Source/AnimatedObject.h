#ifndef __ANIMATEDOBJECT_H
#define __ANIMATEDOBJECT_H

#include <Ogre.h>
#include <string>
#include "ActionType.h"

class AnimatedObject
{
public:
	AnimatedObject();
	~AnimatedObject();
		
	void create(std::string name);
	void setMesh(std::string name, std::string file, unsigned long animations = Action::getFlag(Action::ACT_NUM)-1);

	void setAction(Action::Type action);
	void update(double seconds);
		
	// Sets
	void setPosition(Ogre::Vector3 v) { _node->setPosition(v); }
	void setY(Ogre::Real y) { _node->setPosition(Ogre::Vector3(position().x, y, position().z)); }
	void setRotation(Ogre::Radian x, Ogre::Radian y, Ogre::Radian z) { 
		_node->rotate(Ogre::Vector3(1, 0, 0), x); 
		_node->rotate(Ogre::Vector3(0, 1, 0), y);
		_node->rotate(Ogre::Vector3(0, 0, 1), z);
	}
	void setScale(Ogre::Vector3 v) { _node->scale(v); }

	// Gets
	Ogre::Vector3 position() { return _node->getPosition(); }
	Ogre::Quaternion rotation() { return _node->getOrientation(); }

protected:
	Ogre::Entity *_mesh;
	Ogre::SceneNode *_node;	
	Ogre::AnimationState *_anim[Action::ACT_NUM];
	bool _idleSinceUpdate;

	Action::Type _actionType;
	unsigned long _animations;
};


#endif // __ANIMATEDOBJECT_H
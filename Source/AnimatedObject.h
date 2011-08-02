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
	virtual void setMesh(std::string name, std::string file);

	virtual void update(double seconds);
		
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
	void setAnimation(Ogre::AnimationState *anim, bool loop=true);

	Ogre::Entity *_mesh;
	Ogre::SceneNode *_node;	
	Ogre::AnimationState *_anim;
};


#endif // __ANIMATEDOBJECT_H
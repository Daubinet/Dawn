#ifndef __ANIMATEDOBJECT_H
#define __ANIMATEDOBJECT_H

#include <Ogre.h>
#include <string>

class AnimatedObject
{
public:
	enum ActionType { ANIM_IDLE, ANIM_WALK, ANIM_RUN, ANIM_BATTLE, ANIM_FALL, ANIM_PICKUPONE };

	AnimatedObject();
	~AnimatedObject();
		
	void create(std::string name);
	void setMesh(std::string name, std::string file);

	void walk();
	void idle();
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

private:
	Ogre::Entity *_mesh;
	Ogre::SceneNode *_node;	
	Ogre::AnimationState *_anim, *_idle, *_walk;
	ActionType _actionType;
	bool _idleSinceUpdate;
};


#endif // __ANIMATEDOBJECT_H
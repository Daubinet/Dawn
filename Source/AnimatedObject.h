#ifndef __ANIMATEDOBJECT_H
#define __ANIMATEDOBJECT_H

#include <Ogre.h>
#include <string>

class AnimatedObject
{
public:
	AnimatedObject();
	~AnimatedObject();
		
	void create(std::string name);
	void setMesh(std::string name, std::string file);

	void update(double seconds);
	void animate(std::string animName);
	
	// Sets
	void setPosition(Ogre::Vector3 v) { _node->setPosition(v); }
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
	Ogre::AnimationState *_anim;
};


#endif // __ANIMATEDOBJECT_H
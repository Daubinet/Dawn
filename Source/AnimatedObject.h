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
	
	void setPosition(Ogre::Vector3 v);

private:
	Ogre::Entity *_mesh;
	Ogre::SceneNode *_node;	
	Ogre::AnimationState *_anim;
};


#endif // __ANIMATEDOBJECT_H
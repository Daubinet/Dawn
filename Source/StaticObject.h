#ifndef __STATICOBJECT_H
#define __STATICOBJECT_H

#include <Ogre.h>
#include <vector>

class StaticObject
{
public:
	StaticObject();
	~StaticObject();

	void create(std::string name);
	void setMesh(std::string name, std::string file);

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
	std::string _name;
};


#endif // __STATICOBJECT_H

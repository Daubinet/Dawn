#ifndef __STATICOBJECT_H
#define __STATICOBJECT_H

#include <Ogre.h>
#include <vector>

class StaticObject
{
public:
	StaticObject() { _object = NULL; _objnode = NULL; }
	//StaticObject(std::string name, std::string filename);
	StaticObject(std::string name, Ogre::Entity* obj, Ogre::SceneNode* node);
	StaticObject(std::string name, Ogre::Entity* obj, Ogre::SceneNode* node, Ogre::Vector3 position);
	~StaticObject();

	//Loads the object
	Ogre::Entity* getEntity();

	//getting the scenenode with the object attached
	Ogre::SceneNode* getSceneNode();

	//gets The name of the loaded item
	std::string getName() const { return( _objname != "") ? _objname : NULL; } 

	// Sets
	 void setPosition(float x, float y, float z);
	inline void setRotation(Ogre::Vector3 rotation) { }

	
	inline Ogre::Vector3 position() const
	{
		if(_objnode == NULL)
			return Ogre::Vector3(1.0, 1.0, 1.0);
		else
			return _objnode->getPosition();
	}

	inline Ogre::Vector3 rotation() const
	{ 
		return Ogre::Vector3();
	}

private:
	Ogre::Entity* _object;
	Ogre::SceneNode* _objnode;
	std::string _objname;
};


#endif // __STATICOBJECT_H

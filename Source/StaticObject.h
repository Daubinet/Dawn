#ifndef __STATICOBJECT_H
#define __STATICOBJECT_H

#include <Ogre.h>
#include <vector>

class StaticObject
{
public:
	StaticObject(std::string name, std::string filename);
	~StaticObject();

	// Sets
	inline void setPosition(Ogre::Vector3 position) { }
	inline void setRotation(Ogre::Vector3 rotation) { }

	inline Ogre::Vector3 position() const
	{
		return Ogre::Vector3();
	}
	inline Ogre::Vector3 rotation() const
	{ 
		return Ogre::Vector3();
	}

protected:
};


#endif // __STATICOBJECT_H

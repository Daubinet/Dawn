#include "StaticObject.h"
/*
StaticObject::StaticObject(std::string name, std::string filename)
{
	_object = NULL;  /*
						TODO FILL THIS FUNCTION
					 
	
} */
StaticObject::StaticObject(std::string name, Ogre::Entity* obj, Ogre::SceneNode* node)
{

	_object = obj;
	_objname = name;
	_objnode = node;
	_objnode->setPosition( 1.0, 1.0, 1.0);
	
} 
StaticObject::StaticObject(std::string name, Ogre::Entity* obj, Ogre::SceneNode* node, Ogre::Vector3 position)
{

	_object = obj;
	_objname = name;
	_objnode = node;
	_objnode->setPosition( position);
	
} 
Ogre::Entity* StaticObject::getEntity()
{
	
	return (_object != NULL) ? _object : NULL;  //if object is not null the return object else return a NULL
}
Ogre::SceneNode* StaticObject::getSceneNode()
{
	return (_objnode != NULL) ? _objnode : NULL;
}
void StaticObject::setPosition(float x, float y, float z)
{		
	_objnode->setPosition((Ogre::Real)x,(Ogre::Real) y,(Ogre::Real) z);
}

StaticObject::~StaticObject()
{
}
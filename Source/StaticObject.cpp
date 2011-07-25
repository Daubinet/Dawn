#include "StaticObject.h"
#include "Globals.h"

StaticObject::StaticObject()
: _node(NULL), _mesh(NULL)
{
}

StaticObject::~StaticObject()
{
}

void StaticObject::create(std::string name)
{
	if(_node)
		delete _node;
	_node = gSceneManager->getRootSceneNode()->createChildSceneNode(name);
}

void StaticObject::setMesh(std::string name, std::string file)
{
	if(_mesh)
		delete _mesh;
	_mesh = gSceneManager->createEntity(name, file);
	_node->attachObject(_mesh);
}

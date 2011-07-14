#include <string>
#include "StaticObject.h"

StaticObject::StaticObject(std::string filename, ISceneNode *parent, ISceneManager *sceneIrr, int id)
: CMeshSceneNode(sceneIrr->getMesh(filename.c_str()), parent, sceneIrr, id)
{
}

StaticObject::~StaticObject()
{
}

/*
void StaticObject::setNode(ISceneManager *sceneIrr, std::string filename) 
{
	_mesh = sceneIrr->getMesh(filename.c_str());
	_node = sceneIrr->addMeshSceneNode(_mesh);
}

void StaticObject::setSelector(irr::scene::ISceneManager *gSceneManager, irr::scene::ITriangleSelector *selector)
{
	selector = gSceneManager->createTriangleSelector(_mesh, _node);
	setTriangleSelector(selector);
	selector->drop();
}

vector3df StaticObject::direction()
{
	matrix4 transf = getAbsoluteTransformation();
	vector3df dir = vector3df(0.0f, 0.0f, 1.0f);
	transf.rotateVect(dir);
	return dir;
}
vector3df StaticObject::position()
{
	return getPosition();
}
vector3df StaticObject::rotation()
{
	return getRotation();
}

void StaticObject::setScale(vector3df scale)
{
	setScale(scale);
}
*/
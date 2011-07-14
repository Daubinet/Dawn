#include "AnimObject.h"
#include "Globals.h"

AnimObject::AnimObject(std::string filename, std::string filename2, scene::ISceneNode* parent, scene::ISceneManager* sceneIrr, s32 id)
: scene::CAnimatedMeshSceneNode(sceneIrr->getMesh(filename.c_str()), parent, sceneIrr, id), _selected(false)
{
	ITexture *texture = gRender->getTexture(filename2.c_str());
	_billboard = sceneIrr->addBillboardSceneNode();
	_billboard->setMaterialTexture(0, texture);
	_billboard->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	_billboard->setVisible(false);
}

AnimObject::~AnimObject()
{
}

// Sets
void AnimObject::select()
{
	_selected = true;
	showBillboard();
}

void AnimObject::deselect()
{
	_selected = false;
	hideBillboard();
}

void AnimObject::showBillboard()
{
	_billboard->setVisible(true);
}
void AnimObject::hideBillboard()
{
	_billboard->setVisible(false);
}

/*
void AnimObject::setSelector(irr::scene::ISceneManager *gSceneManager, irr::scene::ITriangleSelector *selector)
{
	selector = gSceneManager->createTriangleSelector(_node);
	setTriangleSelector(selector);
	selector->drop();
}


void AnimObject::drop()
{
	getMesh()->drop();
	drop();
}

void AnimObject::setMaterial(ITexture *texture)
{
	setMaterialFlag(EMF_LIGHTING, true);
	setMaterialTexture(0, texture);
}

void AnimObject::setPosition(vector3df position)
{
	setPosition(position);
	_billboard->setPosition(position + vector3df(0, 15, 0));
}

void AnimObject::setRotation(vector3df rotation)
{
	setRotation(rotation);
}

void AnimObject::setScale(vector3df scale)
{
	setScale(scale);
}

// Gets
*/
vector3df AnimObject::getDirection()
{
	matrix4 transf = getAbsoluteTransformation();
	vector3df dir = vector3df(0.0f, 0.0f, 1.0f);
	transf.rotateVect(dir);
	return dir;
}
/*
vector3df AnimObject::position()
{
	return getPosition();
}
vector3df AnimObject::rotation()
{
	return getRotation();
}
*/

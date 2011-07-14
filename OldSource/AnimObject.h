#ifndef __ANIMOBJECT_H
#define __ANIMOBJECT_H

#include <string>
#include <irrlicht.h>
#include "AuxIrr/CAnimatedMeshSceneNode.h"
#include "ObjectType.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class AnimObject : public scene::CAnimatedMeshSceneNode
{
public:
	// Create/destroy
	AnimObject(std::string filename, std::string filename2, scene::ISceneNode* parent, scene::ISceneManager* sceneIrr, s32 id);
	~AnimObject();

	// Load
	void drop();
	
	// Billboard
	void showBillboard();
	void hideBillboard();

	// Sets
	virtual void select();
	virtual void deselect();
	void setSelector(irr::scene::ISceneManager *gSceneManager, irr::scene::ITriangleSelector *selector);

	// Gets
	virtual vector3df getDirection();

protected:
	bool _selected;
	IBillboardSceneNode *_billboard;
};

#endif // __ANIMOBJECT_H

#ifndef __STATICOBJECT_H
#define __STATICOBJECT_H

#include <vector>
#include <irrlicht.h>
#include "Item.h"
#include "ObjectType.h"
#include "AuxIrr/CMeshSceneNode.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class StaticObject : public CMeshSceneNode
{
public:
	StaticObject(std::string filename, ISceneNode *parent, ISceneManager *sceneIrr, int id = ObjectType::OBJ_None);
	~StaticObject();

	/*
	void setNode();
	void setSelector(irr::scene::ISceneManager *gSceneManager, irr::scene::ITriangleSelector *selector);

	// Sets
	inline void setPosition(vector3df position) { setPosition(position); }
	inline void setRotation(vector3df rotation) { setRotation(rotation); }
	void setScale(vector3df scale);
	inline void setMesh(IMesh *mesh) { _mesh = mesh; }
	inline void setMaterial(ITexture *texture) { 
		setMaterialFlag(EMF_LIGHTING, true);
		setMaterialTexture( 0, texture); 
	}
	inline void setItems() {
		_items.clear();
		for(int i = 0; i < 3; ++i)
			_items.push_back(i);
	}

	// Gets
	inline bool hasItems() const { return !_items.empty(); }

	inline vector3df position() const
	{ 
		if(_node == NULL) return vector3df();
		return getPosition();
	}
	inline vector3df rotation() const
	{ 
		if(_node == NULL) return vector3df();
		return getRotation();
	}
	inline IMesh *mesh() { return _mesh; }
	inline IMeshSceneNode *node() { return _node; }

	virtual vector3df direction();
	virtual vector3df position(); 
	virtual vector3df rotation(); 

protected:
	IMesh *_mesh;
	 *_node;
	 */

	std::vector<int> _items;
};


#endif // __OBJECT_H

#ifndef __OBJECTTYPE_H
#define __OBJECTTYPE_H

#include <irrlicht.h>
using namespace irr;
using namespace core;

class ObjectType
{
public:
	enum {
			OBJ_None = 0, OBJ_COLLECT = 1,
			OBJ_NPC_SELL = 2, OBJ_NPC_QUEST = 4, OBJ_MOB = 8, OBJ_Total = 4 
	};
};

#endif //__OBJECTTYPE_H
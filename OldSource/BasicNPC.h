#ifndef __BASICNPC_H
#define __BASICNPC_H

#include "AI.h"
#include "Object.h"

#include "EventReceiver.h"
class BasicNPC : public Object, public AI, public EventReceiver
{
public:

	BasicNPC();


	//get
	bool isInRange(Object obj);
	bool isClicked();
	//set

	//members
protected:


};
#endif

#include "BasicNPC.h"
#include <irrMath.h>

BasicNPC::BasicNPC()
{

}

bool BasicNPC::isInRange(Object obj)
{
	

	//create a rect arround the npc
	if(position().X+30 > obj.position().X && position().X-30 < obj.position().X && position().Y+30 > obj.position().Y && position().Y-30 < obj.position().Y)
	{
	return true;
	}
	return false;




}

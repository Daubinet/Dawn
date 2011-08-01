#include "Mob.h"


void Mob::MoveToTarget(Creature target)
{
		if(getDistance(target).x+2  < 0 )
			moveTo(position() - Ogre::Vector3(0.1, 0, 0));
		 if(getDistance(target).x-2  > 0)
			moveTo(position() + Ogre::Vector3(0.1, 0, 0));
		 if(getDistance(target).z+2 < 0)
			moveTo(position() - Ogre::Vector3(0, 0, 0.1));
		 if(getDistance(target).z-2 > 0)
			moveTo(position() + Ogre::Vector3(0, 0, 0.1));
		 if(getDistance(target).y+2 < 0 )
			moveTo(position() - Ogre::Vector3(0, 0.1,0));
		 if(getDistance(target).y-2 > 0 )
			 moveTo(position() + Ogre::Vector3(0, 0.1, 0));
			
		
}
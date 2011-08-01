#include "Creature.h"

Creature::Creature() : m_state(ALIVE), m_health(100)
{
}


void Creature::onDeath()
{
	if(getState() == DEATH)
		animate("Fall");
}
DeathState Creature::getState()
{
	if(m_health <= 0)
		return DEATH;
	else
		return ALIVE;
}
CreatureFaction Creature::getTargetFaction(Creature target)
{
	return target.getFaction();
}
void Creature::setAnimatedState(CreatureAnimatedState ani)
{
	switch(ani)
	{
	case IDLE:
		//animate("idle"); // it crash
		break;
	case RUN:
		animate("Run");
		break;
	case WALK:
		animate("Walk");
		break;
	default:
		//animate("Idle"); it crash
		break;
	}
	update(0.1);

}
void Creature::getRotate( Creature target)
{
	Ogre::Real tx =target.rotation().x; // target rotation x
	Ogre::Real ty =target.rotation().y; //target rotation y
	Ogre::Real tz =target.rotation().z; //target rotation z

	Ogre::Real cx =rotation().x; //creature rotation x
	Ogre::Real cy =rotation().y;//creature rotation y
	Ogre::Real cz =rotation().z; //creature rotation z

	Ogre::Real ncx =0; //new Creature rotation  x, y, z 
	Ogre::Real ncy =0;
	Ogre::Real ncz =0;

	ncx =(tx - cx < 0)? + (tx - cx) : - (tx -cx);  //if target rotation minus creature rotation is lower then 0

	
	
}

Ogre::Vector3 Creature::getDistance(Creature target)
{
	return (target.position() - position());
}

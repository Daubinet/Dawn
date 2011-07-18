#ifndef __ITutorial01_h_
#define __ITutorial01_h_  

#include "BaseApp.h"
#include <deque>  

class ITutorial01 : public BaseApplication {
public: 
	ITutorial01(void); 
	virtual ~ITutorial01(void);
protected: 
	virtual void createScene(void); 
	virtual void createFrameListener(void);  
	virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt); 
	virtual bool nextLocation(void);  

	Ogre::Real mDistance; 
	// The distance the object has left to travel 
	Ogre::Vector3 mDirection; 
	// The direction the object is moving 
	Ogre::Vector3 mDestination; 
	// The destination the object is moving towards  
	Ogre::AnimationState *mAnimationState; // The current animation state of the object  
	Ogre::Entity *mEntity; // The Entity we are animating 
	Ogre::SceneNode *mNode; // The -SceneNode that the Entity is attached to 
	std::deque<Ogre::Vector3> mWalkList; // The list of points we are walking to 
	Ogre::Real mWalkSpeed; // The speed at which the object is moving
};  

#endif 

#include "Game.h"  
//------------------------------------------------------------------------------------- 
ITutorial01::ITutorial01(void) { } 

//------------------------------------------------------------------------------------- 
ITutorial01::~ITutorial01(void) { }  

//------------------------------------------------------------------------------------- 
void ITutorial01::createScene(void) { 
	// Set the default lighting. 
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f)); 
	// Create the entity 
	mEntity = mSceneMgr->createEntity("Robot", "robot.mesh");  
	// Create the scene node 
	mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("RobotNode", Ogre::Vector3(0.0f, 0.0f, 25.0f)); 
	mNode->attachObject(mEntity); 
	// Create the walking list 
	mWalkList.push_back(Ogre::Vector3(550.0f, 0.0f, 50.0f )); 
	mWalkList.push_back(Ogre::Vector3(-100.0f, 0.0f, -200.0f)); 
	// Create objects so we can see movement
	Ogre::Entity *ent; Ogre::SceneNode *node;  ent = mSceneMgr->createEntity("Knot1", "knot.mesh"); 
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot1Node", Ogre::Vector3(0.0f, -10.0f, 25.0f)); 
	node->attachObject(ent); node->setScale(0.1f, 0.1f, 0.1f);  ent = mSceneMgr->createEntity("Knot2", "knot.mesh"); 
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot2Node", Ogre::Vector3(550.0f, -10.0f, 50.0f)); 
	node->attachObject(ent); node->setScale(0.1f, 0.1f, 0.1f);  ent = mSceneMgr->createEntity("Knot3", "knot.mesh"); 
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot3Node", Ogre::Vector3(-100.0f, -10.0f,-200.0f)); 
	node->attachObject(ent); node->setScale(0.1f, 0.1f, 0.1f);  
	
	// Set the camera to look at our handiwork 
	mCamera->setPosition(90.0f, 280.0f, 535.0f); 
	mCamera->pitch(Ogre::Degree(-30.0f)); 
	mCamera->yaw(Ogre::Degree(-15.0f)); 
} 

void ITutorial01::createFrameListener(void)
{
	BaseApplication::createFrameListener(); 
	// Set idle animation 
	mAnimationState = mEntity->getAnimationState("Idle"); 
	mAnimationState->setLoop(true); 
	mAnimationState->setEnabled(true); 
	// Set default values for variables 
	mWalkSpeed = 35.0f; 
	mDirection = Ogre::Vector3::ZERO; 
}  

bool ITutorial01::nextLocation(void)
{ 
	if (mWalkList.empty()) 
		return false; 
	mDestination = mWalkList.front();
	// this gets the front of the deque
	mWalkList.pop_front(); 
	// this removes the front of the deque 
	mDirection = mDestination - mNode->getPosition();
	mDistance = mDirection.normalise(); return true;
} 

bool ITutorial01::frameRenderingQueued(const Ogre::FrameEvent &evt)
{ 
	if (mDirection == Ogre::Vector3::ZERO) 
	{ 
		if (nextLocation()) {
			// Set walking animation 
			mAnimationState = mEntity->getAnimationState("Walk");
			mAnimationState->setLoop(true); mAnimationState->setEnabled(true);	  
		}//if 
	}
		else
		{ 
			Ogre::Real move = mWalkSpeed * evt.timeSinceLastFrame; mDistance -= move; 
			if (mDistance <= 0.0f)
			{  mNode->setPosition(mDestination); mDirection = Ogre::Vector3::ZERO;	  
			// Set animation based on if the robot has another point to walk to.  
			if (!nextLocation())
			{ 
				// Set Idle animation  
				mAnimationState = mEntity->getAnimationState("Idle");
				mAnimationState->setLoop(true); mAnimationState->setEnabled(true); }
			else
			{ 
					// Rotation Code will go here later 
					Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X; if ((1.0f + src.dotProduct(mDirection)) < 0.0001f) { mNode->yaw(Ogre::Degree(180));	  
					}
					else
					{ Ogre::Quaternion quat = src.getRotationTo(mDirection); mNode->rotate(quat); } // else
				}//else 
			}
			else
			{ mNode->translate(mDirection * move); 
			} // else
		} // if 
		mAnimationState->addTime(evt.timeSinceLastFrame); return BaseApplication::frameRenderingQueued(evt); 
	}  

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
#define WIN32_LEAN_AND_MEAN 
#include "windows.h" 
#endif  
#ifdef __cplusplus 
extern "C" { 
#endif  
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
			INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT ) 
#else int main(int argc, char *argv[]) 
#endif 
{
	// Create application object 
	ITutorial01 app;  
	try { app.go(); } 
	catch( Ogre::Exception& e ) 
	{ 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
		MessageBox( NULL, (LPCWSTR)e.getFullDescription().c_str(), L"An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL); 
#else 
		std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl; 
#endif 
	}  
	return 0; }  
#ifdef __cplusplus 
} 
#endif
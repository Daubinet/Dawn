#ifndef __BasicTutorial3_h_ 
#define __BasicTutorial3_h_  

#include "BaseApp.h"
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

class BasicTutorial3 : public BaseApplication {
private: Ogre::TerrainGlobalOptions* mTerrainGlobals; Ogre::TerrainGroup* mTerrainGroup; bool mTerrainsImported; OgreBites::Label* mInfoLabel;  
		 
		 void defineTerrain(long x, long y); void initBlendMaps(Ogre::Terrain* terrain); void configureTerrainDefaults(Ogre::Light* light); 
public: BasicTutorial3(void); virtual ~BasicTutorial3(void);  protected: virtual void createScene(void); virtual void createFrameListener(void); virtual void destroyScene(void); virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt); };  

#endif // __BasicTutorial3_h_
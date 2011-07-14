#include <CEGUI.h> 
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "BaseApp.h"

class BasicTutorial7 : public BaseApplication 
{ 
public: 
	BasicTutorial7(void); 
	virtual ~BasicTutorial7(void);

protected: 
	CEGUI::OgreRenderer* mRenderer;  
	
	virtual void createScene(void);  
	virtual void createFrameListener(void);  
	// Ogre::FrameListener 
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);  
	// OIS::KeyListener 
	virtual bool keyPressed( const OIS::KeyEvent &arg ); 
	virtual bool keyReleased( const OIS::KeyEvent &arg ); 
	// OIS::MouseListener 
	virtual bool mouseMoved( const OIS::MouseEvent &arg ); 
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ); 
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );  bool quit(const CEGUI::EventArgs &e); 
};
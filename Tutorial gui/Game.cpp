#include "Game.h"

//------------------------------------------------------------------------------------- 
BasicTutorial7::BasicTutorial7(void) { } 
//------------------------------------------------------------------------------------- 
BasicTutorial7::~BasicTutorial7(void) { } 
//------------------------------------------------------------------------------------- 
void BasicTutorial7::createScene(void) { } 
//------------------------------------------------------------------------------------- 
void BasicTutorial7::createFrameListener(void) { BaseApplication::createFrameListener(); } 
//------------------------------------------------------------------------------------- 
bool BasicTutorial7::frameRenderingQueued(const Ogre::FrameEvent& evt) { return BaseApplication::frameRenderingQueued(evt); } 
//------------------------------------------------------------------------------------- 
bool BasicTutorial7::keyPressed( const OIS::KeyEvent &arg ) { return BaseApplication::keyPressed(arg); } 
//------------------------------------------------------------------------------------- 
bool BasicTutorial7::keyReleased( const OIS::KeyEvent &arg ) { return BaseApplication::keyReleased(arg); } 
//------------------------------------------------------------------------------------- 
bool BasicTutorial7::mouseMoved( const OIS::MouseEvent &arg ) { return BaseApplication::mouseMoved(arg); }
//------------------------------------------------------------------------------------- 
bool BasicTutorial7::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) { return BaseApplication::mousePressed(arg, id); } 
//-------------------------------------------------------------------------------------
bool BasicTutorial7::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) { return BaseApplication::mouseReleased(arg, id); } 
//------------------------------------------------------------------------------------- 
bool BasicTutorial7::quit(const CEGUI::EventArgs &e) { return true; }

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
#define WIN32_LEAN_AND_MEAN 
#include "windows.h" 
#endif  
#ifdef __cplusplus 
extern "C" { 
#endif  
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT ) 
#else 
	int main(int argc, char *argv[]) 
#endif 
	{

	BasicTutorial7 app;  
	try { app.go(); } 
	catch( Ogre::Exception& e ) { 

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox( NULL, (LPCWSTR)(e.getFullDescription().c_str()), L"An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else 
		std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl; 
#endif 
	}
	return 0; 
}  

#ifdef __cplusplus 
} 
#endif
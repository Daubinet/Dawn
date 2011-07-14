#ifndef __GLOBALS_H
#define __GLOBALS_H

#include <string>
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;

class EventReceiver;
class Database;
class GameInfo;
class SceneManager;
class Text;
class Connection;
class Protocol;
class DB;

// Irrlicht
extern IrrlichtDevice *gDevice;
extern IVideoDriver *gRender; 
extern ITimer *gTimer;

extern SceneManager gSceneManager;
extern EventReceiver gEventReceiver;
extern GameInfo gGameInfo;
extern int gScreenWidth, gScreenHeight;

// Resources
extern Text gText;
extern DB gDB;

extern double distance(vector3df v1, vector3df v2);
extern std::string toString(int number);

#endif //__GLOBALS_H
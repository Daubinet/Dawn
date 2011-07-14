#include "DatabaseConstants.h"
#include "EventReceiver.h"
#include "Globals.h"
#include "GameInfo.h"
#include "SceneManager.h"
#include "Text.h"

// Irrlicht
IrrlichtDevice *gDevice;
IVideoDriver *gRender;
ITimer *gTimer;

// Info
EventReceiver gEventReceiver;
SceneManager gSceneManager;
GameInfo gGameInfo;
int gScreenWidth, gScreenHeight;

// Resources
Text gText;
DB gDB;

double distance(vector3df v1, vector3df v2)
{
	float x = v1.X-v2.X;
	float y = v1.Y-v2.Y;
	float z = v1.Z-v2.Z;
	return sqrt(x*x + y*y + z*z);
}

extern std::string toString(int number)
{
	std::string str;
	while(number > 0)
	{
		str = char((number%10)+'0') + str;
		number /= 10;
	}
	return str;
}

/*
App.h
*/

#ifndef __CLIENT_H
#define __CLIENT_H

#include <irrlicht.h>

class Client
{
public:
	Client();
	~Client();
	void exit();

	bool initialize();
	void run();
};

#endif // __CLIENT_H

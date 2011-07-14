//  Models.h
//
//  Soulmen
//
// Library: <LibraryName>
// Package: <PackageName>
// Module: <ModuleName>
//
// Description Load models  quickly into the source.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
//#ifdef _MOELS_H
#define MOELS_H

#include <irrlicht.h>

using namespace irr;
using namespace scene;

class Models
{
public:
	// COnstructor 
	Models(ISceneManager &mgr);

	//Loads the moddels
	ISceneNode* ModelLoader(const char* filepath);

	// load models with  x position y position and z position
	ISceneNode* ModelLoader(const char* filepath, int posx, int posy, int posz);

	// filepath position x y z  rotation x y z
  ISceneNode* ModelLoader(const char* filepath, int posx, int posy, int posz, int rotx, int roty, int rotz); 

  

  // destructor 
  ~Models();

private:

ISceneManager *mgr; // Scene manager
ISceneNode* model; // Node for the model
};
//#endif
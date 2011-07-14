#ifndef __SPRITE3D_H
#define __SPRITE3D_H

#include <irrlicht.h>
#include "Globals.h"

using namespace irr;

class SpriteShader : public video::IShaderConstantSetCallBack
{
public:

	virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
	{
		video::IVideoDriver* driver = services->getVideoDriver();

		// set inverted world matrix
		// if we are using highlevel shaders (the user can select this when
		// starting the program), we must set the constants by name.

		core::matrix4 invWorld = driver->getTransform(video::ETS_WORLD);
		invWorld.makeInverse();

		if (UseHighLevelShaders)
			services->setVertexShaderConstant("mInvWorld", invWorld.pointer(), 16);
		else
			services->setVertexShaderConstant(invWorld.pointer(), 0, 4);

		// set clip matrix

		core::matrix4 worldViewProj;
		worldViewProj = driver->getTransform(video::ETS_PROJECTION);
		worldViewProj *= driver->getTransform(video::ETS_VIEW);
		worldViewProj *= driver->getTransform(video::ETS_WORLD);

		if (UseHighLevelShaders)
			services->setVertexShaderConstant("mWorldViewProj", worldViewProj.pointer(), 16);
		else
			services->setVertexShaderConstant(worldViewProj.pointer(), 4, 4);

		// set camera position

		core::vector3df pos = gDevice->getSceneManager()->
			getActiveCamera()->getAbsolutePosition();

		if (UseHighLevelShaders)
			services->setVertexShaderConstant("mLightPos", reinterpret_cast<f32*>(&pos), 3);
		else
			services->setVertexShaderConstant(reinterpret_cast<f32*>(&pos), 8, 1);

		// set light color

		video::SColorf col(0.0f,1.0f,1.0f,0.0f);

		if (UseHighLevelShaders)
			services->setVertexShaderConstant("mLightColor",
					reinterpret_cast<f32*>(&col), 4);
		else
			services->setVertexShaderConstant(reinterpret_cast<f32*>(&col), 9, 1);

		// set transposed world matrix

		core::matrix4 world = driver->getTransform(video::ETS_WORLD);
		world = world.getTransposed();

		if (UseHighLevelShaders)
			services->setVertexShaderConstant("mTransWorld", world.pointer(), 16);
		else
			services->setVertexShaderConstant(world.pointer(), 10, 4);
	}

private:
	bool UseHighLevelShaders;
	io::path vsFileName; // filename for the vertex shader
	io::path psFileName; // filename for the pixel shader
};


class Sprite3D
{
public:
	Sprite3D();
	~Sprite3D();

	void createMaterials(io::path vsFileName, io::path psFileName);
	s32 newMaterialType1() { return _newMaterialType1; }
	s32 newMaterialType2() { return _newMaterialType2; }
	SpriteShader *shader() { return _shader; }

private:
	s32 _newMaterialType1;
	s32 _newMaterialType2;

	SpriteShader *_shader;
};


#endif // __SPRITE3D_H
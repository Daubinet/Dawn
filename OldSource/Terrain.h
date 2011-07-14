#ifndef __TERRAIN_H
#define __TERRAIN_H

#include <string>
#include <irrlicht.h>

using namespace irr;

class Terrain : scene::ISceneNode
{
public:

    Terrain(const io::path& heightMapPath, scene::ISceneNode* parent, scene::ISceneManager* gSceneManager, s32 id);

    ~Terrain();

    virtual void render();

    virtual const core::aabbox3d<f32>& getBoundingBox() const;

    virtual video::SMaterial& getMaterial( u32 num );

    virtual void OnRegisterSceneNode();

    virtual u32 getMaterialCount() const;

    void getHeight(core::vector3df& position);

private:

    f32 _minX;

    f32 _maxX;

    f32 _minZ;

    f32 _maxZ;

    f32 _maxHeightValue;

    f32 _vertexSpacing;

    s32 _heightMapWidth;

    s32 _heightMapHeight;

    core::aabbox3d<f32> _boundingBox;

    video::S3DVertexTangents* _vertices;

    video::SMaterial _material;

    f32** _heightValues;

    u16* _indices;

    u16 _indexBufferLength;

    core::vector2di fromWorldPositionToHeightmapCoordinate(const core::vector3df& position);

    core::vector3df fromHeightmapCoordinateToWorldPosition(const core::vector2di& heightmapCoordinate);

};


#endif // __TERRAIN_H
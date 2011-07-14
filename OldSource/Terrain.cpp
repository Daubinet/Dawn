#include "boost/math/special_functions/fpclassify.hpp"
#include "irrMath.h"
#include "Terrain.h"

Terrain::Terrain(const io::path& heightMapPath, scene::ISceneNode* parent, scene::ISceneManager* gSceneManager, s32 id )
: scene::ISceneNode(parent, gSceneManager, id)
{
    _maxHeightValue = 32.0f;
    _vertexSpacing = 8.0f;

    _material.Wireframe = true;
    _material.Lighting = false;
    _material.FrontfaceCulling=true;

    //Load the heightmap file.
    video::IImage* heightMap = SceneManager->getVideoDriver()->createImageFromFile(heightMapPath);

    //Define the height value for each terrain vertex based on the heightmap data.
    {
        _heightMapHeight = heightMap->getDimension().Height;
        _heightMapWidth =heightMap->getDimension().Width;
        _heightValues = new f32*[_heightMapWidth];
        for (s32 i = 0; i < _heightMapWidth; ++i)
            _heightValues[i] = new f32[_heightMapHeight];
        for (s32 x = 0; x < _heightMapWidth; ++x)
            for (s32 y = 0; y < _heightMapHeight; ++y)
                _heightValues[x][y] = _maxHeightValue * (heightMap->getPixel(x, y).getRed() / 255.0f);
    }

    _vertices = new video::S3DVertexTangents[_heightMapHeight * _heightMapWidth];

    //Define position and texture coordinates for each terrain vertex.
    {
        f32 x = _heightMapWidth * _vertexSpacing * -0.5f;
        f32 z = _heightMapHeight * _vertexSpacing * -0.5f;
        _minX = x;
        _maxX = x + (_heightMapWidth * _vertexSpacing);
        _minZ = z;
        f32 u = 0.0f;
        f32 v = 0.0f;
        f32 uDerivative = 1.0f / (_heightMapWidth - 1);
        f32 vDerivative = 1.0f / (_heightMapHeight - 1);
        s32 vertexCount = 0;
        _boundingBox.reset(x,_heightValues[0][0],z);
        for (s32 j = 0; j < _heightMapHeight; ++j)
        {
            for (s32 i = 0; i < _heightMapWidth; ++i)
            {
                _vertices[vertexCount].Pos.X = x;
                _vertices[vertexCount].Pos.Y = _heightValues[i][j];
                _vertices[vertexCount].Pos.Z = z;
                _boundingBox.addInternalPoint(_vertices[vertexCount].Pos);
                _vertices[vertexCount].TCoords.X = u;
                _vertices[vertexCount].TCoords.X = v;
                ++vertexCount;
                u += uDerivative;
                x += _vertexSpacing;
            }
            u = 0.0f;
            v += vDerivative;
            x = _heightMapWidth * _vertexSpacing * -0.5f;
            z += _vertexSpacing;
        }
        _maxZ = z;
    }

    s32 indexCount = _heightMapWidth * 2 * (_heightMapHeight - 1);
    if(indexCount > 65535)
        throw std::exception("The heightmap exceeds the 16 bits index buffer limit.");

    _indices = new u16[indexCount];

    //Define the indices.
    {
        s32 i = 0;
        s32 y = 0;
        while (y < _heightMapHeight - 1)
        {
            for (s32 x = 0; x < _heightMapWidth; ++x)
            {
                //_indices[i++] = x + y * _heightMapWidth;
                _indices[i++] = x + (y + 1) * _heightMapWidth;
                _indices[i++] = x + y * _heightMapWidth;
            }
            ++y;
            if (y < _heightMapHeight - 1)
            {
                for (int x = _heightMapWidth - 1; x >= 0; --x)
                {
                    //_indices[i++] = x + (y + 1) * _heightMapWidth;
                    _indices[i++] = x + y * _heightMapWidth;
                    _indices[i++] = x + (y + 1) * _heightMapWidth;
                }
            }
            ++y;
        }
    }

    //Define the normals.
    {
        bool swappedWinding = false;
        core::vector3df firstVector;
        core::vector3df secondVector;
        core::vector3df normal;
        for (s32 i = 2; i < indexCount; ++i)
        {
            firstVector = _vertices[_indices[i - 1]].Pos - _vertices[_indices[i]].Pos;
            secondVector = _vertices[_indices[i - 2]].Pos - _vertices[_indices[i]].Pos;
            normal = firstVector.crossProduct(secondVector);
            normal.normalize();
            if (swappedWinding)
                normal *= -1;
            if (!boost::math::isnan(normal.X))
            {
                _vertices[_indices[i]].Normal += normal;
                _vertices[_indices[i - 1]].Normal += normal;
                _vertices[_indices[i - 2]].Normal += normal;
            }
            swappedWinding = !swappedWinding;
        }
        for (s32 i = 0; i < _heightMapHeight * _heightMapWidth; ++i)
            _vertices[i].Normal.normalize();
    }

    //Define the tangents and binormals.
    {
        for (s32 i = 0; i < _heightMapHeight; i++)
            for (s32 j = 0; j < _heightMapWidth; j++)
            {
                s32 vertexIndex = j + i * _heightMapWidth;
                core::vector3df v1 = _vertices[vertexIndex].Pos;
                if (j < _heightMapWidth - 1)
                {
                    core::vector3df v2 = _vertices[vertexIndex + 1].Pos;
                    _vertices[vertexIndex].Tangent = (v2 - v1);
                }
                else
                {
                    core::vector3df v2 = _vertices[vertexIndex - 1].Pos;
                    _vertices[vertexIndex].Tangent = (v1 - v2);
                }
                _vertices[vertexIndex].Tangent.normalize();
                _vertices[vertexIndex].Binormal = _vertices[vertexIndex].Tangent.crossProduct(_vertices[vertexIndex].Normal);
            }
    }

}


Terrain::~Terrain()
{
}

void Terrain::render()
{
    video::IVideoDriver* driver = SceneManager->getVideoDriver();

    driver->setMaterial(_material);
    driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
    driver->drawVertexPrimitiveList(&_vertices[0], _heightMapHeight * _heightMapWidth, &_indices[0], _heightMapWidth * 2 * (_heightMapHeight-1) - 2, video::EVT_TANGENTS, scene::EPT_TRIANGLE_STRIP, video::EIT_16BIT);
}

const core::aabbox3d<f32>& Terrain::getBoundingBox() const
{
    return _boundingBox;
}

video::SMaterial& Terrain::getMaterial( u32 num )
{
    return _material;
}

void Terrain::OnRegisterSceneNode()
{
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}

irr::u32 Terrain::getMaterialCount() const
{
    return 1;
}

void Terrain::getHeight( core::vector3df& position )
{
    core::vector2di lower;
    lower.X = (s32)((position.X + _heightMapWidth * _vertexSpacing * 0.5f) / _vertexSpacing);
    lower.Y = (s32)((position.Z + _heightMapHeight * _vertexSpacing * 0.5f) / _vertexSpacing);
    core::vector2di higher = lower;
    ++higher.X;
    ++higher.Y;
    core::vector3df lowerWorldPosition = fromHeightmapCoordinateToWorldPosition(lower);
    core::vector3df higherWorldPosition = fromHeightmapCoordinateToWorldPosition(higher);
    float xRelative = (position.X - lowerWorldPosition.X) / (higherWorldPosition.X - lowerWorldPosition.X);
    float zRelative = (position.Z - lowerWorldPosition.Z) / (higherWorldPosition.Z - lowerWorldPosition.Z);
    if(xRelative + zRelative < 1.0f)
    {
        position.Y = _heightValues[lower.X][lower.Y];
        position.Y += zRelative * (_heightValues[lower.X][higher.Y] - _heightValues[lower.X][lower.Y]);
        position.Y += xRelative * (_heightValues[higher.X][lower.Y] - _heightValues[lower.X][lower.Y]);
    } 
	else {
        position.Y = _heightValues[higher.X][higher.Y];
        position.Y += (1.0f - zRelative) * (_heightValues[higher.X][lower.Y] - _heightValues[higher.X][higher.Y]);
        position.Y += (1.0f - xRelative) * (_heightValues[lower.X][higher.Y] - _heightValues[higher.X][higher.Y]);
    }
}

core::vector3df Terrain::fromHeightmapCoordinateToWorldPosition( const core::vector2di& heightmapCoordinate )
{
    core::vector3df position;
    position.X = heightmapCoordinate.X * _vertexSpacing + _minX;
    position.Y = _heightValues[heightmapCoordinate.X][heightmapCoordinate.Y];
    position.Z = heightmapCoordinate.Y * _vertexSpacing + _minZ;
    return position;
}

core::vector2di Terrain::fromWorldPositionToHeightmapCoordinate( const core::vector3df& position )
{
    core::vector2di coordinate;
    coordinate.X = (s32)((position.X + (_heightMapWidth - 1) * _vertexSpacing * 0.5f) / _vertexSpacing);
    coordinate.Y = (s32)((position.Z + (_heightMapHeight - 1) * _vertexSpacing * 0.5f) / _vertexSpacing);
    return coordinate;
}

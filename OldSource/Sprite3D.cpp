#include "Sprite3D.h"

Sprite3D::Sprite3D()
{
	_shader = new SpriteShader();
}

Sprite3D::~Sprite3D()
{
	_shader->drop();
}

void Sprite3D::createMaterials(io::path vsFileName, io::path psFileName)
{
	video::IGPUProgrammingServices* gpu = gRender->getGPUProgrammingServices();
	
	_newMaterialType1 = gpu->addHighLevelShaderMaterialFromFiles(
		vsFileName, "vertexMain", video::EVST_VS_2_0,
			psFileName, "pixelMain", video::EPST_PS_2_0,
			this->shader(), video::EMT_SOLID);
} 
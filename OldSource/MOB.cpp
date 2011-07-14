#include "AI.h"
#include "Globals.h"
#include "MOB.h"

MOB::MOB(std::string filename, std::string filename2, scene::ISceneNode* parent, scene::ISceneManager* sceneIrr, s32 id)
: Char(filename, filename2, parent, sceneIrr, id)
{
	ITexture *texture = gRender->getTexture(filename2.c_str());
	_billboard = sceneIrr->addBillboardSceneNode();
	_billboard->setMaterialTexture(0, texture);
	_billboard->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	_billboard->setVisible(false);
}

MOB::~MOB()
{
}

void MOB::patrollArea(int centerX, int centerY, int radius)
{
	_ai.patrollCircularArea(centerX, centerY, radius);
}

void MOB::update(f32 timeScale)
{
	Char::update(timeScale);

	_ai.update();
	switch(_ai.getActionType())
	{
		case ACTION_Stand:
			break;

		case ACTION_Move:
		{
			float x = _ai.getAction().moveX;
			float y = _ai.getAction().moveY;

			float x2 = getPosition().X;
			float y2 = getPosition().Z;

			float x3 = getDirection().X;
			float y3 = getDirection().Z;

			vector2df dir = vector2df(x3, y3);
			vector2df wantedDir = vector2df(x, y) - vector2df(x2, y2);

			// if it is in right position
			if(wantedDir.getLength() < 10.0f) {
				stop();
				break;
			}

			// otherwise, rotate or walk
			float ang = dir.getAngleTrig();
			float ang2 = wantedDir.getAngleTrig();
			float rot = ang - ang2;

			if(rot < -1) {
				turnLeft(timeScale);
				break;
			}
			if(rot > 1) {
				turnRight(timeScale);
				break;
			}

			walk(timeScale);

			break;
		}

	}

}

void MOB::render()
{
	CAnimatedMeshSceneNode::render();
	
	video::SMaterial debug_mat;
	debug_mat.Lighting = false;
	debug_mat.AntiAliasing=0;
	gRender->setMaterial(debug_mat);

	gRender->setTransform(ETS_WORLD, IdentityMatrix);
	gRender->draw3DBox(getTransformedBoundingBox(), video::SColor(255,0,255,0));
	gRender->draw3DBox(getAttackArea(), video::SColor(255,255,0,0));
}

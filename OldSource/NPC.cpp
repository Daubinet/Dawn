#include "Globals.h"
#include "NPC.h"

NPC::NPC(std::string filename, std::string filename2, scene::ISceneNode* parent, scene::ISceneManager* sceneIrr, s32 id)
: Char(filename, filename2, parent, sceneIrr, id)
{
}

NPC::~NPC()
{
}


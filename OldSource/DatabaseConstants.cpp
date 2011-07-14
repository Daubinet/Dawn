#include "DatabaseConstants.h"

DB::DB()
{
	_charInfo[0] = CharFileInfo("../../Data/MOBs/ant01.ms3d", "../../Data/MOBs/AntBillboard.png", "../../Data/MOBs/Ant.ancfg");
	_charInfo[1] = CharFileInfo("../../Data/NPCs/Dwarf.x", "../../Data/NPCs/DwarfBillboard.png", "../../DataNPCs/Dwarf.ancfg");
}

DB::~DB()
{
}

std::string DB::getAnimInfoFromId(int id)
{
	return _charInfo[id].animFile;
}

std::string DB::getMeshFromId(int id)
{
	return _charInfo[id].meshFile;
}

std::string DB::getBillboardFromId(int id)
{
	return _charInfo[id].billboardFile;
}
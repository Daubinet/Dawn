#ifndef __DBCONSTANTS_H
#define __DBCONSTANTS_H

#include <string>

const int FRAMES_PER_SECOND = 100;
const float PLAYER_MOVE_SPEED = 0.15f;
const float PLAYER_ROT_SPEED = 0.8f;
const float NPC_MOVE_SPEED = 0.0f;
const float NPC_ROT_SPEED = 0.0f;
const float MOB_MOVE_SPEED = 0.1f;
const float MOB_ROT_SPEED = 0.5f;

class DB
{
public:
	
	struct CharFileInfo
	{
		std::string meshFile, billboardFile, animFile;

		CharFileInfo() {}
		CharFileInfo(std::string mesh, std::string billboard, std::string animation) {
			meshFile = mesh;
			billboardFile = billboard;
			animFile = animation;
		}
	};

	struct ItemInfo
	{
		int id;
		std::string iconFile;
	};

	DB();
	~DB();

	std::string getAnimInfoFromId(int id);
	std::string getMeshFromId(int id);
	std::string getBillboardFromId(int id);
	
private:
	CharFileInfo _charInfo[2];
	ItemInfo _itemInfo[2];
};

#endif // __DBCONSTANTS_H
/*
CharSelection
*/

#ifndef __CHAR_SELECTION_H
#define __CHAR_SELECTION_H

#include <irrlicht.h>
#include <cstdint>
#include "Char.h"
#include "EventReceiver.h"
#include "InterfaceDefines.h"
#include "AnimObject.h"
#include "Sprite2D.h"

class SceneManager;

class CharSelection
{
public:
	CharSelection();
	~CharSelection();

	bool initialize();

	void handleEvents();
	void update();
	void draw();

	class CharInfo
	{
	public:
		std::string name;
		irr::u32 modelnum;
		irr::u8 race;
		irr::u8 level;
		uint64_t exp;
		irr::u32 server_ip;
		irr::u16 port;
	};

private:
	ISceneManager *_sceneIrr;
	ICameraSceneNode *_camera;

	Sprite2D _background;
	Sprite2D _tab, _selection;
	Sprite2D _charIcon[3];
	std::string _charName[3];
	Sprite2D _enterWorld;
	
	Char *_selectedChar;

	// TODO (nfries88 or rosalia): use this information rather than presets.
	irr::core::list<CharInfo> list;

	irr::u32 lastip;
	irr::u32 thisip;
	irr::u32 premtime;
	irr::u32 lastlogin;


	friend class Protocol;
};

#endif
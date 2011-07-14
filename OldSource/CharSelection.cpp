#include "CharSelection.h"
#include "Globals.h"
#include "SceneManager.h"
#include "Text.h"

CharSelection::CharSelection()
{
}

CharSelection::~CharSelection()
{
}

bool CharSelection::initialize()
{
	_sceneIrr = gDevice->getSceneManager();
	_sceneIrr->clear();

	_tab.setTexture("../../Data/Interface/CharSelectionTab.bmp");
	_tab.setPosition(gScreenWidth - _tab.width(), 0);

	_selection.setTexture("../../Data/Interface/CharSelection.bmp", true);
	_selection.setPosition(gScreenWidth - _tab.width(), 0);

	_background.setTexture("../../Data/Interface/CharSelectionBg.bmp");

	_enterWorld.setTexture("../../Data/Interface/EnterWorld.bmp");
	_enterWorld.setPosition(gScreenWidth - _tab.width() + 50, 700);

	/*
	int charCode[3];
	charCode[0] = database.queryInt(std::string("select * from login where email=\"")+gGameInfo.email()+std::string("\""), "char1");
	charCode[1] = database.queryInt(std::string("select * from login where email=\"")+gGameInfo.email()+std::string("\""), "char2");
	charCode[2] = database.queryInt(std::string("select * from login where email=\"")+gGameInfo.email()+std::string("\""), "char3");
	*/

	for(int i = 0; i < 3; ++i)
	{
		//if(charCode[i] != -1)
		//	_charName[i] = database.queryString("select * from chars where idchar="+Utils::toString(charCode[i]), "name");
		//else
			_charName[i] = "";
	}

	_camera = _sceneIrr->addCameraSceneNode(0, vector3df(0, 0, -10), vector3df(0, 0, 0));
	_sceneIrr->addLightSceneNode(0, core::vector3df(0,100,-10), video::SColorf(1.0f,1.0f,1.0f,1.0f), 1000.0f);

	/*
	std::string charSel;
	_selectedChar.setNode(_sceneIrr, "../../Data/Chars/Human.x", "../../Data/Chars/HumanIcon.png");
	_selectedChar.setPosition(vector3df(-1, -2, 5));
	_selectedChar.setRotation(vector3df(0, 180, 0));
	_selectedChar.stop();
	*/

	return true;
}

void CharSelection::handleEvents()
{
	if(gEventReceiver.keyPress(irr::KEY_RETURN))
	{
		gSceneManager.setContext(SceneManager::CTX_GAME);
	}
}

void CharSelection::update()
{
}

void CharSelection::draw()
{
	_background.draw();
	_tab.draw();
	_selection.draw();
	_enterWorld.draw();

	_sceneIrr->drawAll();

	gText.draw(_charName[0], 1200, 50);
	gText.draw(_charName[1], 1200, 150);
	gText.draw(_charName[2], 1200, 250);
}


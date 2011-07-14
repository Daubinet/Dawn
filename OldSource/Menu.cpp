#include "Globals.h"
#include "Menu.h"
#include "SceneManager.h"

/*TODO Soulmen
-Add buttons to the menu paneel
-Fix problem with loading the main.png
*/

Menu::Menu()
{
}

Menu::~Menu()
{
}

bool Menu::initialize()
{
	texture.setTexture("../../Data/Interface/MainMenu.png", true);
	texture.setPosition((gScreenWidth-texture.width())/2, (gScreenHeight-texture.height())/2);
	return true;
}

void Menu::handleEvents()
{
	if(gEventReceiver.keyPress(irr::KEY_ESCAPE))
	{
		gSceneManager.setContext(SceneManager::CTX_GAME);
	}
}

void Menu::draw()
{
	texture.draw();
}

void Menu::update()
{
}
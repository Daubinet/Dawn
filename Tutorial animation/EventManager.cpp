#include "EventManager.h"

EventManager::EventManager()
{
	for(int i = 0; i < 256; ++i) {
		_keyIm[i] = false;
		_key[i] = false;
		_keyLast[i] = false;
	}
	for(int i = 0; i < 3; ++i) {
		_buttonIm[i] = false;
		_button[i] = false;
		_buttonLast[i] = false;
	}

}

void EventManager::update()
{
	for(int i = 0; i < 256; ++i) {
		_keyLast[i] = _key[i];
		_key[i] = _keyIm[i];
	}
	for(int i = 0; i < 3; ++i) {
		_buttonLast[i] = _button[i];
		_button[i] = _buttonIm[i];
	}
}

void EventManager::keyPressed(const OIS::KeyEvent &arg)
{
	_keyIm[arg.key] = true;
}

void EventManager::keyReleased(const OIS::KeyEvent &arg)
{
	_keyIm[arg.key] = false;
}
#include "EventManager.h"
#include "OgreStringConverter.h"

EventManager::EventManager(unsigned long hWnd)
: _mouse(NULL)
{	
	OIS::ParamList pl;
	pl.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));
	
	_hWnd = hWnd;
	_ois = OIS::InputManager::createInputSystem( pl );
	_mouse = static_cast<OIS::Mouse*>(_ois->createInputObject( OIS::OISMouse, true ));
	_keyboard = static_cast<OIS::Keyboard*>(_ois->createInputObject( OIS::OISKeyboard, true));
	_mouse->setEventCallback(this);
	_keyboard->setEventCallback(this);

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

EventManager::~EventManager()
{
	if (_mouse)
		_ois->destroyInputObject(_mouse);
	if (_keyboard)
		_ois->destroyInputObject(_keyboard);

	OIS::InputManager::destroyInputSystem(_ois);
}

void EventManager::capture()
{
	_mouse->capture();
	_keyboard->capture();

	for(int i = 0; i < 256; ++i) {
		_keyLast[i] = _key[i];
		_key[i] = _keyIm[i];
	}
	for(int i = 0; i < 3; ++i) {
		_buttonLast[i] = _button[i];
		_button[i] = _buttonIm[i];
	}
}

bool EventManager::isPressingKey(OIS::KeyCode keyCode) const
{
	return _key[keyCode];
}

bool EventManager::pressedKey(OIS::KeyCode keyCode)
{
	bool pressedKey = (_key[keyCode])&&(!_keyLast[keyCode]);
	return pressedKey;
}

void EventManager::setWindowExtents(int width, int height)
{
	const OIS::MouseState &ms = _mouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

// MouseListener
bool EventManager::mouseMoved(const OIS::MouseEvent &evt)
{
	return true;
}
bool EventManager::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID)
{
	return true;
}
bool EventManager::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID)
{
	return true;
}
	
// KeyListener
bool EventManager::keyPressed(const OIS::KeyEvent &evt)
{
	_keyIm[evt.key] = true;
	return true;
}
bool EventManager::keyReleased(const OIS::KeyEvent &evt)
{
	_keyIm[evt.key] = false;
	return true;
}
	
// JoyStickListener
bool EventManager::buttonPressed(const OIS::JoyStickEvent &evt, int index)
{
	return true;
}
bool EventManager::buttonReleased(const OIS::JoyStickEvent &evt, int index)
{
	return true;
}
bool EventManager::axisMoved(const OIS::JoyStickEvent &evt, int index)
{
	return true;
}
bool EventManager::povMoved(const OIS::JoyStickEvent &evt, int index)
{
	return true;
}

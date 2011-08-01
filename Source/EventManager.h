#ifndef __EVENTMANAGER_H
#define __EVENTMANAGER_H

#include "OIS/OISEvents.h"
#include "OIS/OISInputManager.h"
#include "OIS/OISMouse.h"
#include "OIS/OISKeyboard.h"
#include "OIS/OISJoystick.h"

class EventManager : public OIS::MouseListener, public OIS::KeyListener, public OIS::JoyStickListener
{
public:
	EventManager(unsigned long hWnd); 
	~EventManager();

	void setWindowExtents(int width, int height);
	void capture();

	// Gets
	bool isPressingKey(OIS::KeyCode keyCode) const;
	bool pressedKey(OIS::KeyCode keyCode);

protected:
	// MouseListener
	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID);
	
	// KeyListener
	bool keyPressed(const OIS::KeyEvent &evt);
	bool keyReleased(const OIS::KeyEvent &evt);
	
	// JoyStickListener
	bool buttonPressed(const OIS::JoyStickEvent &evt, int index);
	bool buttonReleased(const OIS::JoyStickEvent &evt, int index);
	bool axisMoved(const OIS::JoyStickEvent &evt, int index);
	bool povMoved(const OIS::JoyStickEvent &evt, int index);

private:
	OIS::InputManager *_ois;
	OIS::Mouse *_mouse;
	OIS::Keyboard *_keyboard;
	unsigned long _hWnd;

	// Keyboard
	bool _key[256];
    bool _keyIm[256];
	bool _keyLast[256];

	// Mouse
	bool _button[3];
    bool _buttonIm[3];
	bool _buttonLast[3];
};

#endif // __EVENTMANAGER_H
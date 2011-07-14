#ifndef __EVENTMANAGER_H
#define __EVENTMANAGER_H

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>



class EventManager
{
public:
	EventManager();

    void update();
	void keyPressed(const OIS::KeyEvent &arg);
	void keyReleased(const OIS::KeyEvent &arg);
    
	bool isPressingKey(OIS::KeyCode keyCode) const;
	bool keyPress(OIS::KeyCode keyCode);

	bool mouseClickLeft() { return buttonPress(0); }
	bool mouseClickMIddle() { return buttonPress(1); }
	bool mouseClickRight() { return buttonPress(2); }

	int mouseX() const { return _x; }
	int mouseY() const { return _y; }
    
private:
	// Keyboard
    bool _key[256];
	bool _keyLast[256];
	bool _keyIm[256];

	// Mouse
	// 0 - left, 1 - middle, 2 - right
	bool isPressingButton(int buttonCode) const;
	bool buttonPress(int buttonCode);

	bool _button[3];
	bool _buttonLast[3];
	bool _buttonIm[3];
	int _x, _y;
};

#endif // __EVENTMANAGER_H
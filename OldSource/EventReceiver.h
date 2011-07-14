#ifndef __EVENTRECEIVER_H
#define __EVENTRECEIVER_H

#include <irrlicht.h>

using namespace irr;

class EventReceiver : public IEventReceiver
{
public:
	EventReceiver();

    void update();
	virtual bool OnEvent(const SEvent& event);
    
	bool isPressingKey(EKEY_CODE keyCode) const;
	bool keyPress(EKEY_CODE keyCode);

	bool mouseClickLeft() { return buttonPress(0); }
	bool mouseClickMIddle() { return buttonPress(1); }
	bool mouseClickRight() { return buttonPress(2); }

	s32 mouseX() const { return _x; }
	s32 mouseY() const { return _y; }
    
private:
	// Keyboard
    bool _keyIm[KEY_KEY_CODES_COUNT];

	bool _key[KEY_KEY_CODES_COUNT];
	bool _keyLast[KEY_KEY_CODES_COUNT];

	// Mouse
	// 0 - left, 1 - middle, 2 - right
	bool isPressingButton(int buttonCode) const;
	bool buttonPress(int buttonCode);

	bool _buttonIm[3];
	bool _button[3];
	bool _buttonLast[3];
	s32 _x, _y;
};

#endif
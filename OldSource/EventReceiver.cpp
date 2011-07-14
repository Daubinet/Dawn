#include "EventReceiver.h"

using namespace irr;

EventReceiver::EventReceiver()
{
	for(u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i) {
		_keyIm[i] = false;
		_key[i] = false;
		_keyLast[i] = false;
	}
	for(u32 i = 0; i < 3; ++i) {
		_buttonIm[i] = false;
		_button[i] = false;
		_buttonLast[i] = false;
	}

}

void EventReceiver::update()
{
	for(u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i) {
		_keyLast[i] = _key[i];
		_key[i] = _keyIm[i];
	}
	for(u32 i = 0; i < 3; ++i) {
		_buttonLast[i] = _button[i];
		_button[i] = _buttonIm[i];
	}
}

// This is the one method that we have to implement
bool EventReceiver::OnEvent(const SEvent& event)
{
	// Keyboard
	if(event.EventType == irr::EET_KEY_INPUT_EVENT) 
	{
		_keyIm[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}

	// Mouse
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch(event.MouseInput.Event)
		{
		case EMIE_LMOUSE_PRESSED_DOWN:
			_buttonIm[0] = true;
			break;

		case EMIE_LMOUSE_LEFT_UP:
			_buttonIm[0] = false;
			break;

		case EMIE_MOUSE_MOVED:
			_x = event.MouseInput.X;
			_y = event.MouseInput.Y;
			break;

		default:
			// We won't use the wheel
			break;
		}
	}

    return false;
}

bool EventReceiver::isPressingKey(EKEY_CODE keyCode) const
{
	return _key[keyCode];
}

bool EventReceiver::keyPress(EKEY_CODE keyCode)
{
	bool pressedKey = (_key[keyCode])&&(!_keyLast[keyCode]);
	return pressedKey;
}

// 0 - left, 1 - middle, 2 - right
bool EventReceiver::isPressingButton(int buttonCode) const
{
	return _button[buttonCode];
}

bool EventReceiver::buttonPress(int buttonCode)
{
	bool pressedButton = (_button[buttonCode])&&(!_buttonLast[buttonCode]);
	return pressedButton;
}
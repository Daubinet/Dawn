#ifndef __QUESTWINDOW_H
#define __QUESTWINDOW_H

#include "Sprite2D.h"
#include "Window.h"

class QuestWindow : public Window
{
public:
	QuestWindow(std::string filename);
	~QuestWindow();

	virtual void handleEvents();
	virtual void draw();

private:
	Sprite2D _window;
	rect<s32> _buttonExit;
};


#endif //__QUESTWINDOW_H
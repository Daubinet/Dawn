#include "AI.h"

AI::AI()
{
}

 AI::~AI()
{
}

 void  AI::patrollCircularArea(int centerX, int centerY, int radius)
{
	_centerX = centerX;
	_centerY = centerY;

	_lastAction.moveX = centerX;
	_lastAction.moveY = centerY;
	_lastAction.type = ACTION_Move;

	_action.moveX = centerX;
	_action.moveY = centerY;
	_action.type = ACTION_Move;
}

 void AI::update()
 {
	 static int milliseconds = 0;
	 ++milliseconds;

	 if(milliseconds > 3000)
	 { 
		_lastAction.moveX = _action.moveX ;
		_lastAction.moveY = _action.moveY ;
		_lastAction.type = _action.type;

		_action.moveX = _centerX + rand()%250;
		_action.moveY = _centerY + rand()%250;
		_action.moveX -= 125;
		_action.moveY -= 125;
		_action.type = ACTION_Move;

		milliseconds = 0;
	 }
 }

	 /*
	 _action.moveX = 100;
	 _action.moveY = 100;
	 _action.type = ACTION_Move;
	 */

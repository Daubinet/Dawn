#ifndef __AI_H
#define __AI_H

#include <irrlicht.h>

using namespace irr;
using namespace core;

enum ActionType {
	ACTION_Stand,
	ACTION_Move,
	ACTION_Attack
};

struct AIAction
{
	ActionType type;
	int moveX, moveY;
};

class AI
{
public:
	enum Type {
		AI_Patroll
	};

	// Create/destroy
	AI();
	~AI();

	// Update
	void update();

	// Set behavior
	void patrollCircularArea(int centerX, int centerY, int radius);

	// Gets
	AIAction getAction() { return _action; }
	ActionType getActionType() { return _action.type; }

private:
	AIAction _action, _lastAction;
	int _centerX, _centerY, _radius;
};

#endif
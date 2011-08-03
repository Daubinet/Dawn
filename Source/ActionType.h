#ifndef __ACTIONTYPE_H
#define __ACTIONTYPE_H

class Action 
{ 
public:
	enum Type { 
		ACT_IDLE=0, ACT_WALK=1, ACT_RLEFT=2, ACT_RRIGHT=3, ACT_RUN=4, ACT_DIE=5, ACT_BATTLE=6, ACT_FALL=7, 
		ACT_PICK1=8, ACT_NUM=9
	};

	static unsigned long getFlag(Action::Type type) {
		return 1 << type;
	}

};

#endif // __ACTIONTYPE_H
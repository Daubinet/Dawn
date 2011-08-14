#ifndef __ACTIONTYPE_H
#define __ACTIONTYPE_H

class Action 
{ 
public:
	enum Type { 
		ACT_IDLE=0, ACT_WALK=1, ACT_RUN=2, ACT_DIE=3, ACT_BATTLE=4, ACT_FALL=5, 
		ACT_PICK1=6, ACT_NUM=7
	};

	enum Modifier {
		MDF_NONE=0, MDF_LEFT=1, MDF_RIGHT=2, MDF_FRONT=4, MDF_BACK=8
	};

	static unsigned long getFlag(Action::Type type) {
		return 1 << type;
	}

};

#endif // __ACTIONTYPE_H
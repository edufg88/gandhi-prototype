#ifndef __GSMENU_H__
#define __GSMENU_H__

#include "cGameState.h"

class cGSMenu : public cGameState
{
	public:
		virtual void Enter();
		virtual bool Process();
		virtual bool Render();
		virtual void Exit();

	private:
		
};

#endif
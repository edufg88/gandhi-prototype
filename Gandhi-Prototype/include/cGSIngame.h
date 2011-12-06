#ifndef __GSINGAME_H__
#define __GSINGAME_H__

#include "cGameState.h"

class cGSIngame : public cGameState
{
	public:
		virtual void Enter();
		virtual bool Process();
		virtual bool Render();
		virtual void Exit();

	private:
		
};

#endif
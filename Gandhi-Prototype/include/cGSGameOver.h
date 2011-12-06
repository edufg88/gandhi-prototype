#ifndef __GSGAMEOVER_H__
#define __GSGAMEOVER_H__

#include "cGameState.h"

class cGSGameOver : public cGameState
{
	public:
		virtual void Enter();
		virtual bool Process();
		virtual bool Render();
		virtual void Exit();

	private:
		
};

#endif
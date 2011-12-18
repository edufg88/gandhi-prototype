#ifndef __GSGAMEEND_H__
#define __GSGAMEEND_H__

#include "cGameState.h"

class cGSGameEnd : public cGameState
{
	public:
		virtual void Enter();
		virtual bool Process();
		virtual bool Render();
		virtual void Exit();

	private:
		
};

#endif
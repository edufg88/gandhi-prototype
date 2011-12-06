#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

class cGameState
{
	public:
		virtual void Enter() = 0;
		virtual bool Process() = 0;
		virtual bool Render() = 0;
		virtual void Exit() = 0;

	private:
		
};

#endif
#include "cGSIngame.h"
#include "cGame.h"

void cGSIngame::Enter()
{
	cGame::GetInstance()->GetSound()->playCancion();
	delayPasos = 0;
}

bool cGSIngame::Process()
{
	cGame *Game = cGame::GetInstance();
		
	Game->GetSound()->actualizar();
	Game->ProcessOrder();

	if (Game->GetHero()->GetDirection() != DIRNONE)
	{
		if (delayPasos > 15)
		{
			Game->GetSound()->playEfecto("pasos");
			delayPasos = 0;
		}
		else
		{
			delayPasos++;
		}
	}
	//Game->GetHero()->Move();
	
	return true;
}

bool cGSIngame::Render()
{
	return cGraphicsLayer::GetInstance()->RenderInGame();
}

void cGSIngame::Exit()
{
		
}
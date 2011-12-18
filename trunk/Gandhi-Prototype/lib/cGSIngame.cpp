#include "cGSIngame.h"
#include "cGame.h"

void cGSIngame::Enter()
{
	cGame::GetInstance()->GetSound()->playCancion();
}

bool cGSIngame::Process()
{
	cGame *Game = cGame::GetInstance();
		
	Game->GetSound()->actualizar();
	Game->ProcessOrder();

	if (Game->GetHero()->GetDirection() != DIRNONE)
	{
		//Game->GetSound()->playEfecto("pasos");
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
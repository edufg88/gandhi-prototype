#include "cGSIngame.h"
#include "cGame.h"

void cGSIngame::Enter()
{
		
}

bool cGSIngame::Process()
{
	cGame *Game = cGame::GetInstance();
		
	Game->ProcessOrder();
	Game->GetCritter()->Move();
	
	return true;
}

bool cGSIngame::Render()
{
	return cGraphicsLayer::GetInstance()->RenderInGame();
}

void cGSIngame::Exit()
{
		
}
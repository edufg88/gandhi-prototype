#include "cGSIngame.h"
#include "cGame.h"

void cGSIngame::Enter()
{
	cGame *Game = cGame::GetInstance();

	Game->GetSound()->playCancion();
	delayPasos = 0;
	
	Game->Enemies.clear();
	Game->StalkingEnemies.clear();
	Game->HeroBullets.clear();
	Game->EnemyBullets.clear();
	Game->Items.clear();
	Game->GamePoints = 0;

	Game->GetScene()->LoadMap("media/map.txt");
	Game->GetScene()->camx = 0;
	Game->GetScene()->camy = 0;
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
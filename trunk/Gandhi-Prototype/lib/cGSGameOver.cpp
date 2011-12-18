#include "cGSGameOver.h"
#include "cMouse.h"
#include "cGame.h"

void cGSGameOver::Enter()
{
	
}

bool cGSGameOver::Process()
{
	cGame *Game = cGame::GetInstance();
	cMouse *Mouse;
	Mouse = cInputLayer::GetInstance()->GetMouse();
	
	// EFG: Comprobar eventos del raton
	if(Mouse->ButtonDown(LEFT))
	{
		//Play button
		if(Mouse->In(158,263,301,309))
		{
			//EFG: El cambio de estado lo hacemos desde la clase cGame
			Game->ChangeState(new cGSGameOver());
		}
		//Exit button
		else if(Mouse->In(728,263,873,309))
		{
			return false;
		}
	}

	return true;
}

bool cGSGameOver::Render()
{
	return cGraphicsLayer::GetInstance()->RenderGameOver();
}

void cGSGameOver::Exit()
{

}
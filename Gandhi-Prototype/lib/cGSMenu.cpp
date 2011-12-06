#include "cGSMenu.h"
#include "cGSIngame.h"
#include "cMouse.h"
#include "cGame.h"

void cGSMenu::Enter()
{
	
}

bool cGSMenu::Process()
{
	cGame *Game = cGame::GetInstance();
	cMouse *Mouse;
	Mouse = cInputLayer::GetInstance()->GetMouse();
	
	// EFG: Comprobar eventos del raton
	if(Mouse->ButtonDown(LEFT))
	{
		//Play button
		if(Mouse->In(334,236,420,278))
		{
			//EFG: El cambio de estado lo hacemos desde la clase cGame
			Game->ChangeState(new cGSIngame());
		}
		//Exit button
		else if(Mouse->In(426,236,512,278))
		{
			return false;
		}
	}

	return true;
}

bool cGSMenu::Render()
{
	return cGraphicsLayer::GetInstance()->RenderMenu();
}

void cGSMenu::Exit()
{

}
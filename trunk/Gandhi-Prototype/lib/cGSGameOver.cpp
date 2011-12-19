#include "cGSGameOver.h"
#include "cGSMenu.h"
#include "cMouse.h"
#include "cGame.h"
#include "cGSIngame.h"

void cGSGameOver::Enter()
{
	cGame::GetInstance()->GetSound()->stopCancion();
	cGame::GetInstance()->GetSound()->pausar(30);
	cGame::GetInstance()->GetSound()->playEfecto("over");
}

bool cGSGameOver::Process()
{
	cGame *Game = cGame::GetInstance();
	cKeyboard *KeyBoard = cInputLayer::GetInstance()->GetKeyboard();

	if (KeyBoard->KeyDown(DIK_SPACE))
	{
		Game->ChangeState(Game->menu);
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
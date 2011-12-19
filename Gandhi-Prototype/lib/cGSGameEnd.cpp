#include "cGSGameEnd.h"
#include "cMouse.h"
#include "cGame.h"
#include "cGSMenu.h"

void cGSGameEnd::Enter()
{
	cGame::GetInstance()->GetSound()->stopCancion();
	cGame::GetInstance()->GetSound()->playEfecto("over");
}

bool cGSGameEnd::Process()
{
	cGame *Game = cGame::GetInstance();
	cKeyboard *KeyBoard = cInputLayer::GetInstance()->GetKeyboard();

	if (KeyBoard->KeyDown(DIK_SPACE))
	{
		Game->ChangeState(Game->menu);
	}

	return true;
}

bool cGSGameEnd::Render()
{
	return cGraphicsLayer::GetInstance()->RenderGameEnd();
}

void cGSGameEnd::Exit()
{

}
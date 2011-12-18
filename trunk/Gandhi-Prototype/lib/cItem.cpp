#include "cItem.h"
#include "cScene.h"
#include "cHero.h"
#include "cGame.h"

cItem::cItem(int type, int posx, int posy)
{
	//this->type = IT_SHIELD;
	this->type = type;
	SetPosition(posx,posy);
}

cItem::~cItem()
{

}

void cItem::GetRect(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->camx);
	*posy = SCENE_Yo + y - (Scene->camy);

	switch (type)
	{
		case IT_LIFE:
			SetRect(rc, 192, 0, 256, 64);
			break;
		case IT_SHIELD:
			SetRect(rc, 256, 0, 320, 64);
			break;
		case IT_WEAPON_1:
			SetRect(rc, 0, 0, 64, 64);
			break;
		case IT_WEAPON_2:
			SetRect(rc, 64, 0, 128, 64);
			break;
		case IT_WEAPON_3:
			SetRect(rc, 128, 0, 192, 64);
			break;
		default:
			//SetRect(rc, 128, 0, 192, 64);
			break;
	}
}

void cItem::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cItem::GetPosition(int *posx,int *posy)
{
	*posx = x;
	*posy = y;
}
void cItem::SetCell(int cellx,int celly)
{
	//cx = cellx;
	//cy = celly;
	x = cellx*TILE_WIDTH;
	y = celly*TILE_WIDTH;
}
void cItem::GetCell(int *cellx,int *celly)
{
	*cellx = x/TILE_WIDTH;
	*celly = y/TILE_WIDTH;
}

void cItem::GetWorldRect(RECT *rc)
{
	SetRect(rc, x, y, x + ITEM_WIDTH, y + ITEM_HEIGHT);
}

void cItem::Use()
{
	cHero* Hero = cGame::GetInstance()->GetHero();

	switch(type) 
	{
		case IT_LIFE:
			Hero->AddLife(20);
			break;
		case IT_SHIELD:
			Hero->isShielded = true;
			break;
		case IT_WEAPON_1:
			Hero->ChangeWeapon(BULL_1);
			break;
		case IT_WEAPON_2:
			Hero->ChangeWeapon(BULL_2);
			break;
		case IT_WEAPON_3:
			Hero->ChangeWeapon(BULL_3);
			break;
	}
}

#include "cItem.h"
#include "cScene.h"

cItem::cItem(int type, int cx, int cy)
{
	this->type = type;
	SetCell(cx,cy);
}

cItem::~cItem()
{

}

void cItem::GetRect(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->camx);
	*posy = SCENE_Yo + y - (Scene->camy);

	SetRect(rc,160,64,192,96);
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
	switch(type) {
	case IT_LIFE:
		//TODO: Hero.life++;
		break;
	case IT_SHIELD:
		//TODO: Hero.flipa-con-el-shield() xD
		break;
	}
}

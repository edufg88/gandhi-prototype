#include "cItem.h"
#include "cScene.h"

cItem::cItem()
{
	SetPosition(128,128);
	SetCell(3,3);
}

cItem::~cItem()
{

}

void cItem::GetRect(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->cx<<5);
	*posy = SCENE_Yo + y - (Scene->cy<<5);

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
	cx = cellx;
	cy = celly;
}
void cItem::GetCell(int *cellx,int *celly)
{
	*cellx = cx;
	*celly = cy;
}
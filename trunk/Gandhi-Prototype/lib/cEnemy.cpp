#include "cEnemy.h"
#include "cScene.h"

cEnemy::cEnemy()
{
	SetPosition(64,64);
	SetCell(2,2);
}
cEnemy::~cEnemy()
{

}

void cEnemy::GetRect(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->cx<<5);
	*posy = SCENE_Yo + y - (Scene->cy<<5);

	SetRect(rc,128,32,160,64);
}

void cEnemy::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cEnemy::GetPosition(int *posx,int *posy)
{
	*posx = x;
	*posy = y;
}
void cEnemy::SetCell(int cellx,int celly)
{
	cx = cellx;
	cy = celly;
}
void cEnemy::GetCell(int *cellx,int *celly)
{
	*cellx = cx;
	*celly = cy;
}
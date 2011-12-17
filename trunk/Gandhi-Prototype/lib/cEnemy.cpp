#include "cEnemy.h"
#include "cScene.h"
#include "cGame.h"

cEnemy::cEnemy(int type, int cx, int cy)
{
	this->type = type;
	SetCell(cx,cy);

	switch(type) {
	case ENEMY_1:
		life = ENEMY_1_LIFE;
	case ENEMY_2:
		life = ENEMY_2_LIFE;
	}

	Scene = cGame::GetInstance()->GetScene();
}
cEnemy::~cEnemy()
{

}

void cEnemy::GetRect(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->camx);
	*posy = SCENE_Yo + y - (Scene->camy);

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
	//cx = cellx;
	//cy = celly;
	x = cellx*TILE_WIDTH;
	y = celly*TILE_WIDTH;
}
void cEnemy::GetCell(int *cellx,int *celly)
{
	*cellx = x/TILE_WIDTH;
	*celly = y/TILE_WIDTH;
}

void cEnemy::GetWorldRect(RECT *rc)
{
	SetRect(rc, x, y, x + ENEMY_WIDTH, y + ENEMY_HEIGHT);
}

bool cEnemy::Hit(int damage)
{
	life -= damage;
	return life <= 0;
}

void cEnemy::MoveTo(int destcx,int destcy)
{
	// TODO: IA!
	int cx = x/TILE_WIDTH;
	int cy = y/TILE_WIDTH;
	if(Path.IsDone())	Path.Make(cx,cy,destcx,destcy);
	else					Path.ReMake(destcx,destcy);
}

void cEnemy::update()
{
	int mov;
	int cx, cy; //TODO: inutiles

	if(!Path.IsDone())
	{
		mov=Path.NextStep(&x,&y,&cx,&cy);

		if(mov==ARRIVE)
		{
			Path.Done();
			//seq=0;
		}
		else if(mov==CONTINUE)
		{
		}
	}
	//else
	//{
	//	//Moved for attack?
	//	if(attack)
	//	{
	//		shoot=true;
	//		shoot_seq=0;
	//		shoot_delay=0;
	//		attack=false;
	//	}
	//}
}

#include "cEnemy.h"
#include "cScene.h"
#include "cGame.h"
#include <stdlib.h>

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

	weapon = BULL_1;
	weapon_rof = 0;

	Scene = cGame::GetInstance()->GetScene();
	Hero = cGame::GetInstance()->GetHero();
	Game = cGame::GetInstance();
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
	int cx = x/TILE_WIDTH;
	int cy = y/TILE_WIDTH;
	if(Path.IsDone())	Path.Make(cx,cy,destcx,destcy);
	else					Path.ReMake(destcx,destcy);
}

void cEnemy::update()
{
	int mov;
	int cx, cy; //TODO: inutiles

	Shoot();

	if(!Path.IsDone())
	{
		mov=Path.NextStep(&x,&y,&cx,&cy,this);

		if(mov==ARRIVE)
		{
			Path.Done();
			//seq=0;
		}
		else if(mov==STOP)
		{
			//Hero->GetCell(&cx, &cy);
			GetCell(&cx, &cy);
			MoveTo(cx - 1 + rand()%3, cy - 1 + rand()%3);
		}
	}
	else {
		Hero->GetCell(&cx, &cy);
		MoveTo(cx, cy);
	}
}

void cEnemy::Shoot()
{
	int dx = Hero->GetX() - x;
	int dy = Hero->GetY() - y;
	float mod = sqrt(float(dx*dx + dy*dy));

	float dxa = (float)dx/(float)mod;
	float dya = (float)dy/(float)mod;

	if (weapon_rof == bull_rof[weapon])
	{
		// TODO: Aplicar ángulo a la posición original de la bala para que coincida siempre con el arma del personaje
		Game->addEnemyBullet(weapon, x + ENEMY_WIDTH/2 - BULLET_WIDTH/2, y + ENEMY_HEIGHT/2 - BULLET_HEIGHT/2, dxa*bull_speed[weapon], dya*bull_speed[weapon]);
		weapon_rof = 0;
	}
	else
		weapon_rof++;
}

void cEnemy::Die()
{
	Game->addItem(rand()%NUM_ITEMS, x, y);
}

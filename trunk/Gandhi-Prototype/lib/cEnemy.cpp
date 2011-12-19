#include "cEnemy.h"
#include "cScene.h"
#include "cGame.h"
#include <stdlib.h>

cEnemy::cEnemy(int type, int cx, int cy)
{
	this->type = type;
	SetCell(cx,cy);

	life = enemy_life[type];

	weapon = enemy_weapon[type];
	weapon_rof = 0;

	Scene = cGame::GetInstance()->GetScene();
	Hero = cGame::GetInstance()->GetHero();
	Game = cGame::GetInstance();
}
cEnemy::~cEnemy()
{

}

void cEnemy::GetHeadRect(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->camx);
	*posy = SCENE_Yo + y - (Scene->camy);

	switch (type)
	{
		case ENEMY_1:
			SetRect(rc, 320, 0, 384, 64);
			break;
		case ENEMY_2:
			SetRect(rc, 384, 0, 448, 64);
			break;
		case ENEMY_3:
			SetRect(rc, 448, 0, 512, 64);
			break;
	}

	
	
}

void cEnemy::GetBodyRect(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->camx);
	*posy = SCENE_Yo + y - (Scene->camy);

	switch (type)
	{
		case ENEMY_1:
			SetRect(rc, 512, 0, 576, 64);
			break;
		case ENEMY_2:
			SetRect(rc, 576, 0, 640, 64);
			break;
		case ENEMY_3:
			SetRect(rc, 640, 0, 704, 64);
			break;
	}
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
	Game->GamePoints += damage *10;
	life -= damage;
	return life <= 0;
}

void cEnemy::MoveTo(int destcx,int destcy)
{
	int cx = x/TILE_WIDTH;
	int cy = y/TILE_WIDTH;
	if(Path.IsDone()) Path.Make(cx,cy,destcx,destcy);
	else Path.ReMake(destcx,destcy);
}

void cEnemy::update()
{
	int mov;
	int cx, cy;

	Shoot();

	if(!Path.IsDone())
	{
		mov=Path.NextStep(&x,&y,&cx,&cy,this);

		if(mov==ARRIVE)
		{
			Path.Done();
		}
		else if(mov==STOP)
		{
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
	int dx = Hero->GetX() - x - ENEMY_WIDTH/2;
	int dy = Hero->GetY() - y - ENEMY_HEIGHT/2;
	float mod = sqrt(float(dx*dx + dy*dy));

	float dxa = (float)dx/(float)mod;
	float dya = (float)dy/(float)mod;

	if (weapon_rof == bull_rof[weapon]<<1) //<<1 ajuste de dificultad
	{
		Game->addEnemyBullet(weapon, x, y, dxa*bull_speed[weapon], dya*bull_speed[weapon]);
		weapon_rof = 0;
	}
	else
		weapon_rof++;
}

void cEnemy::Die()
{
	int drop = rand()%NUM_ITEMS;

	if(drop == IT_WEAPON) {
		if(Hero->GetWeapon() < weapon && rand()%2) drop = Hero->GetWeapon() + IT_WEAPON_1 + Hero->upgraded;
		else drop = -1;
	}

	if(drop != -1) Game->addItem(drop, x, y);

	Game->GetSound()->playEfecto("explo");
	Game->rumble = 2;

	Game->GamePoints += (type + 1)*150;
}

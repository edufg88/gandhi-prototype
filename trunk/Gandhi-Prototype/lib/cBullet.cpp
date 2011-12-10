#include "cBullet.h"
#include "cGame.h"


cBullet::cBullet( int type, int x, int y, int vx, int vy )
{
	this->type = type;
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
}

cBullet::~cBullet( void )
{

}

bool cBullet::Move()
{
	x += vx;
	y += vy;

	return Scene->map[(y+BULLET_HEIGHT/2)/TILE_WIDTH][(x+BULLET_WIDTH/2)/TILE_WIDTH].walkable;
}

void cBullet::GetRect( RECT *rc,int *posx,int *posy,cScene *Scene )
{
	*posx = SCENE_Xo + x - (Scene->camx);
	*posy = SCENE_Yo + y - (Scene->camy);

	//TODO: textura balas!
	//SetRect(rc,256,0,288,32);
	SetRect(rc,160,64,192,96);
}

void cBullet::GetWorldRect( RECT *rc )
{
	SetRect(rc, x, y, x + BULLET_WIDTH, y + BULLET_HEIGHT);
}

int cBullet::GetDamage()
{
	switch(type) {
	case BULL_1:
		return BULL_1_DAMAGE;
		break;
	case BULL_2:
		return BULL_2_DAMAGE;
		break;
	case BULL_3:
		return BULL_3_DAMAGE;
		break;
	}
}

void cBullet::GetCell( int *cellx,int *celly )
{
	*cellx = x/TILE_WIDTH;
	*celly = y/TILE_WIDTH;
}

//bool cBullet::CollidesWithEnemy()
//{
//	RECT hr;
//	GetWorldRect(&hr);
//	for(list<cEnemy*>::iterator it = Game->Enemies.begin(); it != Game->Enemies.end(); it++) {
//		RECT er;
//		cEnemy* enemy = *it;
//		enemy->GetWorldRect(&er);
//		if(Game->intersect(&hr, &er)) return true;
//	}
//	return false;
//}



#include "cHero.h"
#include "cTrajectory.h"
#include "cScene.h"

cHero::cHero()
{
	SetPosition(384,96);

	seq=0;
	delay=0;
	speed = 4;

	attack=false;
	shoot=false;
	shoot_seq=0;
	shoot_delay=0;
}

cHero::~cHero()
{

}

// EFG: Creo que esto devuelve el rectángulo que hay que coger del mapa de sprites
// Arnau: Yep, y además devuelve la posición relativa en pantalla
void cHero::GetRect(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->camx);
	*posy = SCENE_Yo + y - (Scene->camy);

	SetRect(rc,256,0,288,32);
}

void cHero::GetRectShoot(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->camx);
	*posy = SCENE_Yo + y - (Scene->camy);

	SetRect(rc,shoot_seq<<5,64,(shoot_seq+1)<<5,96);
	switch(shoot_seq)
	{
		case 0:	*posx+=5;	break;
		case 1:	*posx-=2;	break;
		case 2: *posx-=8;	break;
		case 3: *posx-=16;	break;
		case 4: *posx-=24;	break;
		case 5:	*posx-=32;	break;
		case 6: *posx-=32;	break;
		case 7: *posx-=32;	break;
	}
	
	shoot_delay++;
	if(shoot_delay==4)
	{
		shoot_seq++;
		if(shoot_seq==16) shoot_seq=0;
		shoot_delay=0;
	}
}

void cHero::Move(int dir)
{
	switch(dir) {
	case DIRUP:
		y -= speed;
		break;
	case DIRDOWN:
		y += speed;
		break;
	case DIRRIGHT:
		x += speed;
		break;
	case DIRLEFT:
		x -= speed;
		break;
	}
}

void cHero::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
	//cx = posx/32;
	//cy = posy/32;
}

//void cHero::GetPosition(int *posx,int *posy)
//{
//	*posx = x;
//	*posy = y;
//}

void cHero::SetCell(int cellx,int celly)
{
	//cx = cellx;
	//cy = celly;
	x = cellx*TILE_WIDTH;
	y = celly*TILE_WIDTH;
}

void cHero::GetCell(int *cellx,int *celly)
{
	*cellx = x/TILE_WIDTH;
	*celly = y/TILE_WIDTH;
}

bool cHero::GetShooting()
{
	return shoot;
}
bool cHero::IsFiring()
{
	return (shoot_seq<8);
}

int cHero::GetSpeed()
{
	return speed;
}

int cHero::GetX()
{
	return x;
}

int cHero::GetY()
{
	return y;
}

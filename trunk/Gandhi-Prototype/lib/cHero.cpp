
#include "cHero.h"
#include "cTrajectory.h"
#include "cGame.h"

cHero::cHero()
{
	Scene = cGame::GetInstance()->GetScene();

	SetPosition(0,0);

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

bool cHero::Move( int dir )
{
	switch(dir) {
	case DIRUP:
		if(Scene->map[(y-speed+1)/TILE_WIDTH][x/TILE_WIDTH].walkable
			&& Scene->map[(y-speed+1)/TILE_WIDTH][(x+HERO_WIDTH-1)/TILE_WIDTH].walkable) {
			y -= speed;
			return true;
		}
		break;
	case DIRDOWN:
		if(Scene->map[(y+speed-1+HERO_HEIGHT)/TILE_WIDTH][x/TILE_WIDTH].walkable
			&& Scene->map[(y+speed-1+HERO_HEIGHT)/TILE_WIDTH][(x+HERO_WIDTH-1)/TILE_WIDTH].walkable) {
			y += speed;
			return true;
		}
		break;
	case DIRRIGHT:
		if(Scene->map[y/TILE_WIDTH][(x+speed-1+HERO_WIDTH)/TILE_WIDTH].walkable
			&& Scene->map[(y+HERO_HEIGHT-1)/TILE_WIDTH][(x+speed-1+HERO_WIDTH)/TILE_WIDTH].walkable) {
			x += speed;
			return true;
		}
		break;
	case DIRLEFT:
		if(Scene->map[y/TILE_WIDTH][(x-speed+1)/TILE_WIDTH].walkable
			&& Scene->map[(y+HERO_HEIGHT-1)/TILE_WIDTH][(x-speed+1)/TILE_WIDTH].walkable) {
			x -= speed;
			return true;
		}
		break;
	}

	return false;
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


#include "cHero.h"
#include "cTrajectory.h"
#include "cGame.h"

cHero::cHero(int cx, int cy)
{
	Game = cGame::GetInstance();
	Scene = cGame::GetInstance()->GetScene();

	SetCell(cx,cy);

	seq=0;
	delay=0;
	speed = 4;
	life = 100;
	direction = DIRNONE;

	attack=false;
	shoot=false;
	shoot_seq=0;
	shoot_delay=0;

	weapon = BULL_1;
	weapon_rof = 0;
}

cHero::~cHero()
{

}

void cHero::GetRectHead(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->camx);
	*posy = SCENE_Yo + y - (Scene->camy);

	// SetRect(rc, 256, 0, 320, 64); CABEZA DE HUMANO
	SetRect(rc, 448, 0, 512, 64);
}

void cHero::GetRectBody(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->camx);
	*posy = SCENE_Yo + y - (Scene->camy);

	// El cuerpo cambia en función del arma que llevemos
	switch (weapon)
	{
		case BULL_1:
			SetRect(rc, 64, 0, 128, 64);
			break;
		case BULL_2:
			SetRect(rc, 0, 0, 64, 64);
			break;
		case BULL_3:
			SetRect(rc, 128, 0, 192, 64);
			break;
		default:
			SetRect(rc, 192, 0, 256, 64);
			break;
	}
}

void cHero::GetRectLegs(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	switch(direction)
	{
		case DIRNONE:
			SetRect(rc, 704, 64, 768, 128);	
			break;
		default:
			SetRect(rc, seq*64, 128, (seq+1)*64, 192);
			delay++;
			if(delay>=7)
			{
				seq++;
				if(seq>6) seq=0;
				delay=0;
			}
			break;
			/*
		case DIRLEFT:
		case DIRRIGHT:
			SetRect(rc, seq*64, 128, (seq+1)*64, 192);
			delay++;
			if(delay>=4)
			{
				seq++;
				if(seq>6) seq=0;
				delay=0;
			}
			break;
			*/
	}

	*posx = SCENE_Xo + x - (Scene->camx);
	*posy = SCENE_Yo + y - (Scene->camy);
}

void cHero::GetRectShoot(RECT *rc,int *posx,int *posy,cScene *Scene)
{
	*posx = SCENE_Xo + x - (Scene->camx);
	*posy = SCENE_Yo + y - (Scene->camy);

	SetRect(rc,shoot_seq<<TILE_W_SHIFT,64,(shoot_seq+1)<<TILE_W_SHIFT,96);
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
	RECT hr;
	
	direction = dir;

	switch(dir) 
	{
		case DIRUP:
			if(Scene->map[(y-speed+1)/TILE_WIDTH][x/TILE_WIDTH].walkable
				&& Scene->map[(y-speed+1)/TILE_WIDTH][(x+HERO_WIDTH-1)/TILE_WIDTH].walkable) {
				y -= speed;
				GetWorldRect(&hr);
				if(Game->intersectsWithEnemy(&hr)) {
					y += speed;
					return false;
				}
				return true;
			}
			break;
		case DIRDOWN:
			if(Scene->map[(y+speed-1+HERO_HEIGHT)/TILE_WIDTH][x/TILE_WIDTH].walkable
				&& Scene->map[(y+speed-1+HERO_HEIGHT)/TILE_WIDTH][(x+HERO_WIDTH-1)/TILE_WIDTH].walkable) {
				y += speed;
				GetWorldRect(&hr);
				if(Game->intersectsWithEnemy(&hr)) {
					y -= speed;
					return false;
				}
				return true;
			}
			break;
		case DIRRIGHT:
			if(Scene->map[y/TILE_WIDTH][(x+speed-1+HERO_WIDTH)/TILE_WIDTH].walkable
				&& Scene->map[(y+HERO_HEIGHT-1)/TILE_WIDTH][(x+speed-1+HERO_WIDTH)/TILE_WIDTH].walkable) {
				x += speed;
				GetWorldRect(&hr);
				if(Game->intersectsWithEnemy(&hr)) {
					x -= speed;
					return false;
				}
				return true;
			}
			break;
		case DIRLEFT:
			if(Scene->map[y/TILE_WIDTH][(x-speed+1)/TILE_WIDTH].walkable
				&& Scene->map[(y+HERO_HEIGHT-1)/TILE_WIDTH][(x-speed+1)/TILE_WIDTH].walkable) {
				x -= speed;
				GetWorldRect(&hr);
				if(Game->intersectsWithEnemy(&hr)) {
					x += speed;
					return false;
				}
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

void cHero::GetWorldRect(RECT *rc)
{
	SetRect(rc, x, y, x + HERO_WIDTH, y + HERO_HEIGHT);
}

void cHero::ShootAt(int mx, int my)
{
	int dx = (mx + Scene->camx) - x;
	int dy = (my + Scene->camy) - y;
	float mod = sqrt(float(dx*dx + dy*dy));
	
	float dxa = (float)dx/(float)mod;
	float dya = (float)dy/(float)mod;

	if (weapon_rof == bull_rof[weapon])
	{
		// TODO: Aplicar ángulo a la posición original de la bala para que coincida siempre con el arma del personaje
		Game->addHeroBullet(BULL_1, x + HERO_WIDTH/2 - BULLET_WIDTH/2, y + HERO_HEIGHT/2 - BULLET_HEIGHT/2, dxa*bull_speed[weapon], dya*bull_speed[weapon]);
		weapon_rof = 0;
	}
	else
		weapon_rof++;
}

/*
void cHero::ShootAt(int mx, int my)
{
	cout << "(" << mx << ", " << my << ")" << endl;
	int dx = mx - x;
	int dy = my - y;
	float mod = sqrt(float(dx*dx + dy*dy));

	if (weapon_rof == bull_rof[weapon])
	{
		Game->addHeroBullet(BULL_1, x + HERO_WIDTH/2, y + HERO_HEIGHT/2, dx/mod*bull_speed[weapon], dy/mod*bull_speed[weapon]);
		weapon_rof = 0;
	}
	else
		weapon_rof++;
	
}*/

bool cHero::Hit(int damage)
{
	life -= damage;
	return life <= 0;
}

bool cHero::ChangeWeapon(int newWeapon)
{
	if (newWeapon >= 0 && newWeapon <= 2)
	{
		weapon = newWeapon;
		return true;
	}
	else
	{
		return false;
	}
}
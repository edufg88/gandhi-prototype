
#ifndef __HERO_H__
#define __HERO_H__

#include <windows.h>
#include "cScene.h"

#define HERO_WIDTH 64
#define HERO_HEIGHT 64

//Directions
#define DIRUP		0
#define DIRDOWN		1
#define DIRRIGHT	2
#define DIRLEFT		3
#define DIRNONE		4

//class cScene;
class cGame;

class cHero
{
	public:
		cHero();
		virtual ~cHero(void);

		void init(int cx, int cy);
		bool Move(int dir);

		// EFG: Como el personaje está formado por 3 partes distintas, tenemos 3 funciones
		void GetRectLegs(RECT *rc,int *posx,int *posy,cScene *Scene);
		void GetRectBody(RECT *rc,int *posx,int *posy,cScene *Scene);
		void GetRectHead(RECT *rc,int *posx,int *posy,cScene *Scene);
		void GetRectShield(RECT *rc,int *posx,int *posy,cScene *Scene);

		void GetRectLife(RECT *rc,int *posx,int *posy,cScene *Scene);
		void GetRectShoot(RECT *rc,int *posx,int *posy,cScene *Scene);

		void SetPosition(int posx,int posy);

		void SetCell(int cellx,int celly);
		void GetCell(int *cellx,int *celly);

		void ShootAt(int mx, int my);

		int GetLife() { return life; }
		int GetSpeed();
		int GetX();
		int GetY();
		int GetDirection(){ return direction; }
		void GetWorldRect(RECT *rc);
		bool Hit(int damage);
		bool AddLife(int lifeToAdd);

		bool ChangeWeapon (int newWeapon);
		int GetWeapon() { return weapon; }

		int shielded;
		int upgraded;
		int firing;

	private:
		int x,y;		//Position in total map

		int seq;		//Sequence animation control
		int delay;		//Animation delay

		int shoot_seq;	//Shooter sequence animation control
		int shoot_delay;//Shooter animation delay

		int speed; // Velocidad del personaje
		int life;
		int direction; // Dirección en la que está el personaje

		int weapon; // Indica el tipo de arma que lleva (Bullet type)
		int weapon_rof;

		cScene *Scene;
		cGame *Game;
};

#endif
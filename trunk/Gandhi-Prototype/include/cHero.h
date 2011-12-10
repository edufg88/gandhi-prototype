
#ifndef __HERO_H__
#define __HERO_H__

#include <windows.h>
#include "cScene.h"

#define HERO_WIDTH 32
#define HERO_HEIGHT 32

//class cScene;
class cGame;

class cHero
{
	public:
		cHero(int cx, int cy);
		virtual ~cHero(void);

		bool Move(int dir);
		void GetRect(RECT *rc,int *posx,int *posy,cScene *Scene);
		void GetRectLife(RECT *rc,int *posx,int *posy,cScene *Scene);
		void GetRectShoot(RECT *rc,int *posx,int *posy,cScene *Scene);

		void SetPosition(int posx,int posy);
		//void GetPosition(int *posx,int *posy);
		void SetCell(int cellx,int celly);
		void GetCell(int *cellx,int *celly);
		bool GetShooting();
		bool IsFiring();

		void ShootAt(int mx, int my);

		int GetSpeed();
		int GetX();
		int GetY();
		void GetWorldRect(RECT *rc);
		bool Hit(int damage);

	private:
		int x,y;		//Position in total map
		//int cx,cy;		//Cell position in total map

		int seq;		//Sequence animation control
		int delay;		//Animation delay

		bool attack;	//Order to attack established (moving for attack)
		bool shoot;		//Begin attack (to shoot)
		int shoot_seq;	//Shooter sequence animation control
		int shoot_delay;//Shooter animation delay

		int speed; // Velocidad del personaje
		int life;

		cScene *Scene;
		cGame *Game;
};

#endif

#ifndef __HERO_H__
#define __HERO_H__

#include <windows.h>
#include "cScene.h"

#define HERO_WIDTH 32
#define HERO_HEIGHT 32

//class cScene;

class cHero
{
	public:
		cHero(void);
		virtual ~cHero(void);

		void Move(int dir);
		void GetRect(RECT *rc,int *posx,int *posy,cScene *Scene);
		void GetRectLife(RECT *rc,int *posx,int *posy,cScene *Scene);
		void GetRectShoot(RECT *rc,int *posx,int *posy,cScene *Scene);

		void SetPosition(int posx,int posy);
		//void GetPosition(int *posx,int *posy);
		void SetCell(int cellx,int celly);
		void GetCell(int *cellx,int *celly);
		bool GetShooting();
		bool IsFiring();

		int GetSpeed();
		int GetX();
		int GetY();

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
};

#endif
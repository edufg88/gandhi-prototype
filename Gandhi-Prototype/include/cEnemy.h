#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <windows.h>
#include "cBullet.h"
#include "cPath.h"
#include "cScene.h"

#define ENEMY_WIDTH 32
#define ENEMY_HEIGHT 32

#define NUM_ENEMIES 3
#define ENEMY_1 0
#define ENEMY_2 1
#define ENEMY_3 2

//class cGame;
const int enemy_life[3] = {4, 12, 25};
const int enemy_weapon[3] = {BULL_1, BULL_2, BULL_3};
//const int bull_speed[3] = {8, 8, 8};

class cScene;
class cGame;
class cHero;

class cEnemy
{
	public:
		cEnemy(int type, int cx, int cy);
		virtual ~cEnemy(void);

		void GetHeadRect(RECT *rc,int *posx,int *posy,cScene *Scene);
		void GetBodyRect(RECT *rc,int *posx,int *posy,cScene *Scene);
		void SetPosition(int posx,int posy);
		void GetPosition(int *posx,int *posy);
		void SetCell(int cellx,int celly);
		void GetCell(int *cellx,int *celly);

		void GetWorldRect(RECT *rc);
		bool Hit(int damage);
		void MoveTo(int destcx,int destcy);
		void update();
		void Shoot();
		void Die();

	private:
		int x,y;		//Position in total map
		//int cx,cy;		//Cell position in total map
		int type;
		int life;

		int weapon; // Indica el tipo de arma que lleva (Bullet type)
		int weapon_rof;

		cPath Path;
		cScene *Scene;
		cHero *Hero;
		cGame *Game;
};

#endif
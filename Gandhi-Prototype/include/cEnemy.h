#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <windows.h>
#include <cBullet.h>

#define ENEMY_WIDTH 32
#define ENEMY_HEIGHT 32

#define ENEMY_1 0
#define ENEMY_2 1

#define ENEMY_1_BULLET BULL_1
#define ENEMY_2_BULLET BULL_2

#define ENEMY_1_LIFE 5
#define ENEMY_2_LIFE 10

class cScene;

class cEnemy
{
	public:
		cEnemy(int type, int cx, int cy);
		virtual ~cEnemy(void);

		void GetRect(RECT *rc,int *posx,int *posy,cScene *Scene);
		void SetPosition(int posx,int posy);
		void GetPosition(int *posx,int *posy);
		void SetCell(int cellx,int celly);
		void GetCell(int *cellx,int *celly);

		void GetWorldRect(RECT *rc);
		bool Hit(int damage);
		void Move();

	private:
		int x,y;		//Position in total map
		//int cx,cy;		//Cell position in total map
		int type;
		int life;
};

#endif

#ifndef __BULLET_H__
#define __BULLET_H__

#include <windows.h>
#include "cScene.h"

#define BULLET_WIDTH 16
#define BULLET_HEIGHT 16

#define BULL_1 0
#define BULL_2 1
#define BULL_3 2

/*
#define BULL_1_DAMAGE 1
#define BULL_2_DAMAGE 5
#define BULL_3_DAMAGE 10

// Rate Of Fire (Cadencia de las armas)
#define BULL_1_ROF 5
#define BULL_2_ROF 5
#define BULL_3_ROF 10

#define BULL_SPEED 8
*/

//class cGame;
const int bull_rof[3] = {10, 5, 10};
const int bull_dam[3] = {1, 5, 10};
const int bull_speed[3] = {8, 8, 8};

class cBullet
{
public:
	cBullet(int type, int x, int y, int vx, int vy);
	virtual ~cBullet(void);

	bool Move();
	void GetRect(RECT *rc,int *posx,int *posy,cScene *Scene);
	void GetCell(int *cellx,int *celly);
	void GetWorldRect(RECT *rc);
	int GetDamage();

private:
	int type;
	int x,y;		//Position in total map
	//int cx,cy;		//Cell position in total map

	int vx, vy;
	cScene *Scene;
};

#endif
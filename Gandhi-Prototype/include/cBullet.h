
#ifndef __BULLET_H__
#define __BULLET_H__

#include <windows.h>
#include "cScene.h"

#define BULLET_WIDTH 64
#define BULLET_HEIGHT 64

#define BULL_1 0
#define BULL_2 1
#define BULL_3 2

//class cGame;
const int bull_rof[3] = {6, 10, 10};
const int bull_dam[3] = {2, 6, 14};
const int bull_speed[3] = {8, 8, 8};

class cBullet
{
public:
	cBullet(int type, int x, int y, int vx, int vy);
	virtual ~cBullet(void);

	bool Move();
	void GetRect(RECT *rc,int *posx,int *posy,cScene *Scene,float *ang);
	void GetCell(int *cellx,int *celly);
	void GetWorldRect(RECT *rc);
	int GetDamage();

private:
	int type;
	int x,y;		//Position in total map

	float angle;

	int vx, vy;
	cScene *Scene;
};

#endif
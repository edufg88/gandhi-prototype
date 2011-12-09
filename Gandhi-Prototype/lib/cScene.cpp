
#include "cScene.h"
#include "cMouse.h"
#include "cGame.h"
#include <stdio.h>


cScene::cScene()
{
	/*cx=0;
	cy=0;*/
	camx = camy = 0;
}
cScene::~cScene(){}

void cScene::LoadMap(char *file)
{
	int i,j,n;
	
	FILE *f;
	f=fopen(file,"r");

	for(i=0;i<AREA_WIDTH;i++)
	{
		for(j=0;j<AREA_HEIGHT;j++)
		{
			fscanf(f,"%d",&n);
			map[i][j]=n;
		}
	}

	fclose(f);
}

void cScene::Move(int dir)
{
	int speed = cGame::GetInstance()->GetHero()->GetSpeed();

	//map=32x32, visible=20x17 => move=0..32-20,0..32-17=0..12,0..15

	//Up
	if(dir==DIRUP)
	{
		if(camy > 0) camy -= speed;
	}
	//South
	else if(dir==DIRDOWN)
	{
		if(camy < (AREA_HEIGHT-SCENE_HEIGHT)*TILE_WIDTH) camy += speed;
	}
	//West
	if(dir==DIRLEFT)
	{
		if(camx > 0) camx -= speed;
	}
	//East
	else if(dir==DIRRIGHT)
	{
		if(camx < (AREA_WIDTH-SCENE_WIDTH)*TILE_WIDTH) camx += speed;
	}
}

bool cScene::Visible(int cellx,int celly)
{
	int cx, cy;
	getCell(&cx, &cy);
	return ((cellx>=cx)&&(cellx<cx+SCENE_WIDTH)&&(celly>=cy)&&(celly<cy+SCENE_HEIGHT)) ? 1 : 0;
}

void cScene::getCell(int *cx, int *cy) {
	*cx = camx/32;
	*cy = camy/32;
}
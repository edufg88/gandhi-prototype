
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

	fscanf(f,"%d",&n);
	while (n != -1)
	{
		walkableTiles.insert(n);
		fscanf(f,"%d",&n);
	}

	for(i=0;i<AREA_WIDTH;i++)
	{
		for(j=0;j<AREA_HEIGHT;j++)
		{
			fscanf(f,"%d",&n);
			map[i][j].tile = n;
			map[i][j].walkable = walkableTiles.count(n);
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
		int heroY = cGame::GetInstance()->GetHero()->GetY();
		if(camy > 0 && heroY + HERO_HEIGHT/2 + HERO_Y < AREA_HEIGHT*TILE_WIDTH) camy -= speed;
	}
	//South
	else if(dir==DIRDOWN)
	{
		int heroY = cGame::GetInstance()->GetHero()->GetY();
		if(camy < (AREA_HEIGHT-SCENE_HEIGHT)*TILE_WIDTH
			&& heroY + HERO_HEIGHT/2 - HERO_Y > 0) camy += speed;
	}
	//West
	if(dir==DIRLEFT)
	{
		int heroX = cGame::GetInstance()->GetHero()->GetX();
		if(camx > 0 && heroX + HERO_WIDTH/2 + HERO_X < AREA_WIDTH*TILE_WIDTH) camx -= speed;
	}
	//East
	else if(dir==DIRRIGHT)
	{
		int heroX = cGame::GetInstance()->GetHero()->GetX();
		if(camx < (AREA_WIDTH-SCENE_WIDTH)*TILE_WIDTH
			&& heroX + HERO_WIDTH/2 - HERO_X > 0) camx += speed;
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

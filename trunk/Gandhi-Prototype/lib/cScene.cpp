
#include "cScene.h"
#include "cMouse.h"
#include "cGame.h"
#include <stdio.h>
#include <stdlib.h>


cScene::cScene()
{
	/*cx=0;
	cy=0;*/
	camx = camy = 0;
}
cScene::~cScene(){}

void cScene::LoadMap(char *file)
{
	int i,j,n,w = 0;
	
	FILE *f;
	fopen_s(&f, file,"r");

	// Leemos qué tiles son walkables
	fscanf_s(f,"%d",&n);
	while (n != -1)
	{
		walkableTiles.insert(n);
		fscanf_s(f,"%d",&n);
	}

	cGame *Game = cGame::GetInstance();

	// Mapa tiles
	for(i=0;i<AREA_HEIGHT;i++)
	{
		for(j=0;j<AREA_WIDTH;j++)
		{
			fscanf_s(f,"%d",&n);
			map[i][j].tile = n;
			map[i][j].walkable = walkableTiles.count(n);
			if(map[i][j].walkable) {
				if(w == ENEMY_DENSITY) {
					Game->addStalkingEnemy(rand()%NUM_ENEMIES, j, i);
					w = 0;
				}
				else w++;
			}
		}
	}

	// Leemos posición inicial hero
	fscanf_s(f,"%d",&i);
	fscanf_s(f,"%d",&j);
	Game->GetHero()->SetCell(j, i);
	
	// Leemos posición final (meta) del mapa
	fscanf_s(f,"%d",&i);
	fscanf_s(f,"%d",&j);
	//Game->setMapEnd(i, j); //TODO: hacer algo!

	// Items??
	//TODO: prueba añadir item
	Game->addItem(0, 5*TILE_WIDTH, 5*TILE_WIDTH);

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
		if(camy < (AREA_HEIGHT-SCENE_HEIGHT-1)*TILE_WIDTH
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
		if(camx < (AREA_WIDTH-SCENE_WIDTH-2)*TILE_WIDTH
			&& heroX + HERO_WIDTH/2 - HERO_X > 0) camx += speed;
	}
}

bool cScene::Visible(int cellx,int celly)
{
	int cx, cy;
	getCell(&cx, &cy);
	return (cellx>=cx)&&(cellx<=cx+SCENE_WIDTH)&&(celly>=cy)&&(celly<=cy+SCENE_HEIGHT);
}

void cScene::getCell(int *cx, int *cy) {
	*cx = camx/TILE_WIDTH;
	*cy = camy/TILE_WIDTH;
}

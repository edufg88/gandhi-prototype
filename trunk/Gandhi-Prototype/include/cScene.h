#ifndef __SCENE_H__
#define __SCENE_H__

#include <set>

//Resolution
#define SCREEN_RES_X	800
#define SCREEN_RES_Y	600

//Dimensions
#define AREA_WIDTH		32
#define AREA_HEIGHT		32
#define TILE_WIDTH 32

//Visible part
#define SCENE_WIDTH		SCREEN_RES_X/TILE_WIDTH
#define SCENE_HEIGHT	SCREEN_RES_Y/TILE_WIDTH-1 // Arnau: no entiendo el -1 pero arregla cosas...

//Map coordinate beginning
#define SCENE_Xo		0
#define SCENE_Yo		0
#define SCENE_Xf		( SCENE_Xo + (SCENE_WIDTH * TILE_WIDTH) )
#define SCENE_Yf		( SCENE_Yo + (SCENE_HEIGHT * TILE_WIDTH) )

//Posición pantalla Hero excepto en bordes
#define HERO_X	SCREEN_RES_X/2
#define HERO_Y	SCREEN_RES_Y/2

//Directions
#define DIRUP		0
#define DIRDOWN		1
#define DIRRIGHT	2
#define DIRLEFT		3


struct mapCell {
	int tile;
	bool walkable;
};

class cScene
{
	public:
		cScene();
		virtual ~cScene();

		void LoadMap(char *file);
		void Move(int dir);
		bool Visible(int cellx,int celly);

		mapCell map[AREA_HEIGHT][AREA_WIDTH];
		int camx,camy/*,cx,cy*/;

		void getCell(int *cx, int *cy);

	private:
		std::set<int> walkableTiles;

};


#endif

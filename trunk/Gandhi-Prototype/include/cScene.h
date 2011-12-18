#ifndef __SCENE_H__
#define __SCENE_H__

#include <set>

/** 
 La resolucion es 800 x 600 en cualquier caso
 El mapa es de 32 x 32 de momento
 El tamaño de la escena en tiles es 32 x 32
 El tamaño de la escena en pixels es 32*32 x 32*32 = 1024 x 1024
 **/

//Resolution
#define SCREEN_RES_X	1024
#define SCREEN_RES_Y	768

//Dimensions
#define AREA_WIDTH		64
#define AREA_HEIGHT		32
#define TILE_WIDTH 64
#define TILE_W_SHIFT 6

//Visible part
#define SCENE_WIDTH		SCREEN_RES_X/TILE_WIDTH + 1
#define SCENE_HEIGHT	SCREEN_RES_Y/TILE_WIDTH + 1

//Map coordinate beginning
#define SCENE_Xo		0
#define SCENE_Yo		0
#define SCENE_Xf		SCREEN_RES_X 
#define SCENE_Yf		SCREEN_RES_Y
// Arnau: dejo estas comentadas por si lo queremos aprovechar más adelante
//#define SCENE_Xf		( SCENE_Xo + (SCENE_WIDTH * TILE_WIDTH) )
//#define SCENE_Yf		( SCENE_Yo + (SCENE_HEIGHT * TILE_WIDTH) )

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

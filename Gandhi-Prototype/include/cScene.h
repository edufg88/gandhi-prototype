
#ifndef __SCENE_H__
#define __SCENE_H__

//Resolution
#define SCREEN_RES_X	800
#define SCREEN_RES_Y	600

//Visible part
#define SCENE_WIDTH		25
#define SCENE_HEIGHT	20

//Dimension = Area^2
#define SCENE_AREA		32

//Map coordinate beginning
#define SCENE_Xo		0
#define SCENE_Yo		0
#define SCENE_Xf		( SCENE_Xo + (SCENE_WIDTH<<5) )
#define SCENE_Yf		( SCENE_Yo + (SCENE_HEIGHT<<5) )

class cScene
{
	public:
		cScene();
		virtual ~cScene();

		void LoadMap(char *file);
		void Move(int pointer);
		bool Visible(int cellx,int celly);

		int map[SCENE_AREA][SCENE_AREA];
		int cx,cy;
};


#endif

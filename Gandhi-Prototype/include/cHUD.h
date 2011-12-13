
#ifndef __HUD_H__
#define __HUD_H__

#include <windows.h>
#include <cScene.h>

//Resolution
//#define SCREEN_RES_X	800
//#define SCREEN_RES_Y	600

//Parts of the HUD (EFG: Qué elementos mostraremos en el HUD, esto es un ejemplo)
#define LIFE 0
#define POINTS 1
#define WEAPON 2

typedef struct 
{
	int width;
	int height;
	int x;
	int y;
	RECT r;
}HUDElement; 

class cHUD
{
	public:
		cHUD();
		virtual ~cHUD();
		HUDElement Elements[3][5];
};	


#endif

#include "cHUD.h"

cHUD::cHUD()
{
	//EFG: Inicializar los elementos del HUD
	// Por ejemplo...
	HUDElement life;
	life.width = 100;
	life.height = 25;
	life.x = 0;
	life.y = 20;
	Elements[LIFE] = life;
}

cHUD::~cHUD()
{
	//EFG: Inicializar los elementos del HUD
}
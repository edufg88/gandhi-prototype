#include "cHUD.h"

cHUD::cHUD()
{
	// INICIALIZAMOS TODOS LOS ELEMENTOS DEL HUD
	long hr;

	/***********************************/
	/*			    ARMA			   */
	/***********************************/
	HUDElement weapon0;
	weapon0.x = 70;
	weapon0.y = 530;
	SetRect(&weapon0.r, 173, 120, 223, 160);
	Elements[WEAPON][0] = weapon0;

	HUDElement weapon1;
	weapon1.x = 70;
	weapon1.y = 530;
	SetRect(&weapon1.r, 111, 120, 172, 160);
	Elements[WEAPON][1] = weapon1;

	HUDElement weapon2;
	weapon2.x = 70;
	weapon2.y = 530;
	SetRect(&weapon2.r, 50, 120, 111, 160);
	Elements[WEAPON][2] = weapon2;

	HUDElement weapon3;
	weapon3.x = 17;
	weapon3.y = 514;
	SetRect(&weapon3.r, 405, 105, 540, 175);
	Elements[WEAPON][3] = weapon3;

	HUDElement weapon4;
	weapon4.x = 0;
	weapon4.y = 520;
	SetRect(&weapon4.r, 330, 110, 400, 170);
	Elements[WEAPON][4] = weapon4;

	/***********************************/
	/*	            VIDA			   */
	/***********************************/
	HUDElement life0;
	life0.x = 35;
	life0.y = 12;
	SetRect(&life0.r, 400, 0, 450, 50);
	Elements[LIFE][0] = life0;

	HUDElement life1;
	life1.x = 10;
	life1.y = 7;
	SetRect(&life1.r, 0, 0, 330, 65);
	Elements[LIFE][1] = life1;
	
	HUDElement life2;
	life2.x = 0;
	life2.y = 10;
	SetRect(&life2.r, 460, 0, 500, 60);
	Elements[LIFE][2] = life2;

	/***********************************/
	/*			    PUNTOS			   */
	/***********************************/
	HUDElement points0;
	points0.width = 35;
	points0.height = 0;
	SetRect(&points0.r, 650, 20, 800, 100);
	Elements[POINTS][0] = points0;

	HUDElement points1;
	points1.x = 590;
	points1.y = 12;
	SetRect(&points1.r, 570, 0, 610, 55);
	Elements[POINTS][1] = points1;
}

cHUD::~cHUD()
{
	//EFG: Inicializar los elementos del HUD
}
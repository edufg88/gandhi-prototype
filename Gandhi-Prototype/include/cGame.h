
#ifndef __GAME_H__
#define __GAME_H__

#include "cGraphicsLayer.h"
#include "cInputLayer.h"
#include "cScene.h"
#include "cHUD.h"
#include "cSound.h"
#include "cGameState.h"
#include "cHero.h"
#include "cEnemy.h"
#include "cItem.h"
#include "cBullet.h"
#include <list>

#define STATE_MAIN	0
#define STATE_GAME	1

// EFG: Clase principal del juego utilizamos el patrón Singleton
class cGame
{
	public:
		static cGame* GetInstance();
		virtual ~cGame();

		bool Init(HWND hWnd,HINSTANCE hInst,bool exclusive);
		bool Loop(); 
		void Finalize();

		// EFG: Todo esto hay que cambiarlo cuando tengamos nivel, personaje y enemigos
		cGameState* GetState(){ return State; }
		cScene* GetScene() { return Scene; }
		cHUD* GetHUD() { return HUD; }
		cHero* GetHero() { return Hero; }

		// Arnau: Publicos y sin Getter para más comodidad
		std::list<cEnemy*> Enemies;
		std::list<cItem*> Items;
		std::list<cBullet*> HeroBullets;
		std::list<cBullet*> EnemyBullets;
		
		// EFG: Cambia el estado del juego
		bool ChangeState(cGameState* newState);

		// EFG: Necesitamos que de momento sean públicas
		void ProcessOrder();
		bool Render();

		void addEnemy(int type, int cx, int cy);
		void addItem(int type, int cx, int cy);
		void addHero(int cx, int cy);
		void addEnemyBullet(int type, int x, int y, int vx, int vy);
		void addHeroBullet(int type, int x, int y, int vx, int vy);

		//Aux
		bool intersects(RECT *r1, RECT *r2);
		cEnemy* intersectsWithEnemy(RECT *r);


	private:
		static cGame* instance;
		cGame();

		bool LoopInput();
		bool LoopProcess();
		bool LoopOutput();

		void ProcessKeyboard();
		void ProcessCollisions();
		void ProcessEnemies();
		
		// EFG: Ahora son punteros
		cGraphicsLayer* Graphics;
		cInputLayer* Input;
		cSound* Sound;
		cScene* Scene;
		cHUD* HUD;
		cGameState* State;

		cHero* Hero;
};

#endif

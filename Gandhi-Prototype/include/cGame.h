
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

class cGSGameEnd;
class cGSGameOver;
class cGSIngame;
class cGSMenu;

// EFG: Clase principal del juego utilizamos el patr�n Singleton
class cGame
{
	public:
		static cGame* GetInstance();
		virtual ~cGame();

		bool Init(HWND hWnd,HINSTANCE hInst,bool exclusive);
		bool Loop(); 
		void Finalize();

		cGameState* GetState(){ return State; }
		cScene* GetScene() { return Scene; }
		cHUD* GetHUD() { return HUD; }
		cHero* GetHero() { return Hero; }
		cSound* GetSound() { return Sound; }

		// Arnau: Publicos y sin Getter para m�s comodidad
		std::list<cEnemy*> Enemies;
		std::list<cEnemy*> StalkingEnemies;
		std::list<cItem*> Items;
		std::list<cBullet*> HeroBullets;
		std::list<cBullet*> EnemyBullets;
		
		// EFG: Cambia el estado del juego
		bool ChangeState(cGameState* newState);

		// EFG: Necesitamos que de momento sean p�blicas
		void ProcessOrder();
		bool Render();

		void addEnemy(int type, int cx, int cy);
		void addStalkingEnemy(int type, int cx, int cy);
		void addItem(int type, int posx, int posy);
		void addEnemyBullet(int type, int x, int y, int vx, int vy);
		void addHeroBullet(int type, int x, int y, int vx, int vy);
		void addLevelEnd(int cx, int cy);

		//Aux
		bool intersects(RECT *r1, RECT *r2);
		cEnemy* intersectsWithEnemy(RECT *r);
		cEnemy* intersectsWithEnemy(RECT *r, cEnemy *self);

		int GamePoints;
		int rumble;

		cGSGameEnd* gameEnd;
		cGSGameOver* gameOver;
		cGSIngame* inGame;
		cGSMenu* menu;

	private:
		static cGame* instance;
		cGame();

		bool LoopInput();
		bool LoopProcess();
		bool LoopOutput();

		void ProcessKeyboard();
		void ProcessCollisions();
		void ProcessEnemies();

		cGraphicsLayer* Graphics;
		cInputLayer* Input;
		cSound* Sound;
		cScene* Scene;
		cHUD* HUD;
		cGameState* State;
		cHero* Hero;

		
};

#endif

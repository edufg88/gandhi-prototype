
#ifndef __GAME_H__
#define __GAME_H__

#include "cGraphicsLayer.h"
#include "cInputLayer.h"
#include "cScene.h"
#include "cSound.h"
#include "cGameState.h"

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
		cScene* GetScene() { return &Scene; }
		cCritter* GetCritter() { return &Critter; }
		cSkeleton* GetSkeleton() { return &Skeleton; }

		// EFG: Cambia el estado del juego
		bool ChangeState(cGameState* newState);

		// EFG: Necesitamos que de momento sean públicas
		void ProcessOrder();
		bool Render();

	private:
		static cGame* instance;
		cGame();

		bool LoopInput();
		bool LoopProcess();
		bool LoopOutput();

		// EFG: Ahora son punteros
		cGraphicsLayer* Graphics;
		cInputLayer* Input;
		cSound* Sound;

		cScene Scene;
		cCritter Critter;
		cSkeleton Skeleton;
	
		cGameState* State;
};

#endif

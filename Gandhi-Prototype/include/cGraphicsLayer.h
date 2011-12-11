
#ifndef __GRAPHICSLAYER_H__
#define __GRAPHICSLAYER_H__


#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxerr8.lib")
#pragma comment(lib,"winmm.lib")

#include <D3D9.h>
#include <D3DX9.h>
#include "cScene.h"
#include "cMouse.h"

class cGame;

class cGraphicsLayer  
{
	public:
		static cGraphicsLayer* GetInstance();
		virtual ~cGraphicsLayer();

		bool Init(HWND hWnd, bool windowed); 
		void Finalize();
	
		void LoadData();
		void UnLoadData();
	

		// EFG: Ahora Graphics Layer tiene acceso a todos los parámetros porque tiene acceso a la clase cGame
		// bool Render();
		bool RenderMenu();
		bool RenderInGame();
		bool RenderGameOver();
		
		bool DrawLevel();
		bool DrawHUD();
		bool DrawHero();
		bool DrawEnemies();
		bool DrawItems();
		bool DrawMouse();
		bool DrawRect(RECT rc, D3DCOLOR color);
		//bool Render(int state,cMouse *Mouse,cScene *Scene,cCritter *Critter,cSkeleton *Skeleton);
		//bool DrawScene(cScene *Scene);
		//bool DrawUnits(cScene *Scene,cCritter *Critter,cSkeleton *Skeleton);
		//bool DrawMouse(cMouse *Mouse);
		//bool DrawRect(RECT rc, D3DCOLOR color);

	private:
		static cGraphicsLayer* instance;
		cGraphicsLayer();

		cGame* Game;

		LPDIRECT3D9 g_pD3D;
		LPDIRECT3DDEVICE9 g_pD3DDevice;
		LPD3DXSPRITE g_pSprite;

		// TEXTURAS
		LPDIRECT3DTEXTURE9 texMain,texGame;
		LPDIRECT3DTEXTURE9 texTiles,texCharacters,texMouse;
		LPDIRECT3DTEXTURE9 texHUD, texChar; // EFG: Estas son las nuevas

		ID3DXFont *g_font;

};


#endif

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
class cBullet;

class cGraphicsLayer  
{
	public:
		static cGraphicsLayer* GetInstance();
		virtual ~cGraphicsLayer();

		bool Init(HWND hWnd, bool windowed); 
		void Finalize();
	
		void LoadData();
		void UnLoadData();
	
		bool RenderMenu();
		bool RenderInGame();
		bool RenderGameOver();
		bool RenderGameEnd();
		
		bool DrawLevel();
		bool DrawHUD();
		bool DrawHero();
		void DrawBullet(cBullet *Bullet);
		bool DrawEnemies();
		bool DrawItems();
		bool DrawMouse();
		bool DrawRect(RECT rc, D3DCOLOR color);

	private:
		static cGraphicsLayer* instance;
		cGraphicsLayer();
		cGame* Game;

		LPDIRECT3D9 g_pD3D;
		LPDIRECT3DDEVICE9 g_pD3DDevice;
		LPD3DXSPRITE g_pSprite;

		// TEXTURAS
		LPDIRECT3DTEXTURE9 texMain,texGame, texGameOver, texGameEnd;
		LPDIRECT3DTEXTURE9 texTiles,texMouse;
		LPDIRECT3DTEXTURE9 texHUD, texChar;

		ID3DXFont *g_font;

};


#endif

#include "cGraphicsLayer.h"
#include "cGame.h"
#include "cLog.h"
#include <stdio.h>

cGraphicsLayer* cGraphicsLayer::instance = NULL;

cGraphicsLayer* cGraphicsLayer::GetInstance()
{
	if (instance == NULL)
		instance = new cGraphicsLayer();
	
	return instance;
}

cGraphicsLayer::cGraphicsLayer()
{
	g_pD3D = NULL;
	g_pD3DDevice = NULL;
	g_pSprite = NULL;
}

cGraphicsLayer::~cGraphicsLayer(){}

bool cGraphicsLayer::Init(HWND hWnd)
{
	cLog *Log = cLog::Instance();
	HRESULT hr;

	D3DVIEWPORT9 viewPort = { 0, 0, SCREEN_RES_X, SCREEN_RES_Y, 0.0f, 1.0f };

	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	if(g_pD3D==NULL)
	{
		Log->Msg("Error creating Direct3D object");
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );

	d3dpp.Windowed               = FALSE;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;	//Efficient page flipping
	d3dpp.BackBufferWidth        = SCREEN_RES_X;
    d3dpp.BackBufferHeight       = SCREEN_RES_Y;
    d3dpp.BackBufferFormat       = D3DFMT_X8R8G8B8;

	hr = g_pD3D->CreateDevice(	D3DADAPTER_DEFAULT, 
								D3DDEVTYPE_HAL, 
								hWnd,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								&d3dpp, 
								&g_pD3DDevice );
	if(FAILED(hr))
	{
		Log->Error(hr,"Creating Direct3D device");
		return false;
	}

	// Configure for 2d operations
    hr = g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    hr = g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	hr = g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	if(FAILED(hr))
	{
		Log->Error(hr,"Setting render state");
		return false;
	}

	hr = g_pD3DDevice->SetViewport(&viewPort);
	if(FAILED(hr))
	{
		Log->Error(hr,"Setting viewport");
		return false;
	}

	return true;
}

void cGraphicsLayer::Finalize()
{
	if(g_pD3DDevice)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	if(g_pD3D)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

void cGraphicsLayer::LoadData()
{
	D3DXCreateSprite( g_pD3DDevice, &g_pSprite ); 

	//Main menu
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"media/imgs/main.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								NULL,NULL,NULL,&texMain);
	//GUI game
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"media/imgs/game.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								NULL,NULL,NULL,&texGame);
	//Tiles
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"media/imgs/tiles.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								0x00ff00ff,NULL,NULL,&texTiles);
	//Characters
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"media/imgs/characters.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								0x00ff00ff,NULL,NULL,&texCharacters);
	//Mouse pointers
	D3DXCreateTextureFromFileEx(g_pD3DDevice,"media/imgs/mouse.png",0,0,1,0,D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,D3DX_FILTER_NONE,D3DX_FILTER_NONE,
								0x00ff00ff,NULL,NULL,&texMouse);
}

void cGraphicsLayer::UnLoadData()
{
	if(texMain)
	{
		texMain->Release();
		texMain = NULL;
	}
	if(texGame)
	{
		texGame->Release();
		texGame = NULL;
	}
	if(texTiles)
	{
		texTiles->Release();
		texTiles = NULL;
	}
	if(texCharacters)
	{
		texCharacters->Release();
		texCharacters = NULL;
	}
	if(texMouse)
	{
		texMouse->Release();
		texMouse = NULL;
	}
	if(g_pSprite)
	{
		g_pSprite->Release();
		g_pSprite = NULL;
	}
}

bool cGraphicsLayer::RenderMenu()
{
	cGame* game = cGame::GetInstance();

	g_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0xFF000000, 0, 0 );
	g_pD3DDevice->BeginScene();

	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	g_pSprite->Draw(texMain,NULL,NULL,&D3DXVECTOR3(0.0f,0.0f,0.0f),0xFFFFFFFF);
	g_pSprite->End();

	DrawMouse();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present( NULL, NULL, NULL, NULL );

	return true;
}

bool cGraphicsLayer::RenderInGame()
{
	cGame* game = cGame::GetInstance();

	g_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0xFF000000, 0, 0 );
	g_pD3DDevice->BeginScene();

	//--- SPRITES ---
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//Graphic User Interface
	g_pSprite->Draw(texGame,NULL,NULL,&D3DXVECTOR3(0.0f,0.0f,0.0f),0xFFFFFFFF);
	DrawLevel();
	DrawHero();
	DrawEnemies();
	//DrawHUD();

	g_pSprite->End();

	DrawMouse();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present( NULL, NULL, NULL, NULL );

	return true;
}

bool cGraphicsLayer::DrawLevel()
{
	cScene* Scene = cGame::GetInstance()->GetScene();
	
	RECT rc;
	int x,y,n,
		fx,fy,
		pantx,panty;

	//Tile based map
	fx=Scene->cx+SCENE_WIDTH;
	fy=Scene->cy+SCENE_HEIGHT;

	for(y=Scene->cy;y<fy;y++)
	{
		panty = SCENE_Yo + ((y-Scene->cy)<<5);

		for(x=Scene->cx;x<fx;x++)
		{
			pantx = SCENE_Xo + ((x-Scene->cx)<<5);

			n = Scene->map[y][x];
			SetRect(&rc,n<<5,0,(n+1)<<5,32);
			g_pSprite->Draw(texTiles,&rc,NULL, 
							&D3DXVECTOR3(float(pantx),float(panty),0.0f), 
							0xFFFFFFFF);
		}
	}

	return true;
}

bool cGraphicsLayer::DrawHero()
{
	int cx,cy,posx,posy;
	RECT rc;

	cCritter* Critter = cGame::GetInstance()->GetCritter();
	cScene* Scene = cGame::GetInstance()->GetScene();

	//Draw Critter
	Critter->GetCell(&cx,&cy);
	if(Scene->Visible(cx,cy))
	{
		Critter->GetRect(&rc,&posx,&posy,Scene);
		g_pSprite->Draw(texCharacters,&rc,NULL, 
						&D3DXVECTOR3(float(posx),float(posy),0.0f), 
						0xFFFFFFFF);
		if(Critter->GetSelected())
		{
			Critter->GetRectLife(&rc,&posx,&posy,Scene);
			g_pSprite->Draw(texMouse,&rc,NULL, 
							&D3DXVECTOR3(float(posx),float(posy),0.0f), 
							0xFFFFFFFF);
		}
	}
	Critter->GetRectRadar(&rc,&posx,&posy);
	g_pSprite->Draw(texTiles,&rc,NULL, 
					&D3DXVECTOR3(float(posx),float(posy),0.0f), 
					0xFFFFFFFF);

	return true;
}

bool cGraphicsLayer::DrawEnemies()
{
	int cx,cy,posx,posy;
	RECT rc;

	cSkeleton* Skeleton = cGame::GetInstance()->GetSkeleton();
	cScene* Scene = cGame::GetInstance()->GetScene();
	cMouse* Mouse = cInputLayer::GetInstance()->GetMouse();
	
	//Draw Skeleton
	Skeleton->GetCell(&cx,&cy);
	if(Scene->Visible(cx,cy))
	{
		Skeleton->GetRect(&rc,&posx,&posy,Scene);

		////////////// Arnau: Prueba rotaciones
		D3DXMATRIX preChange, matRotate;
		D3DXVECTOR2 vCenter(16.0f, 16.0f);
		D3DXVECTOR2 vPosition(posx, posy);
		int mPosx, mPosy;
		float deg;

		g_pSprite->GetTransform(&preChange);

		Mouse->GetPosition(&mPosx, &mPosy);

		deg = atan2(float(mPosy-posy),float(mPosx-posx));

		D3DXMatrixTransformation2D(&matRotate, NULL, NULL, NULL, &vCenter, deg, &vPosition);

		g_pSprite->SetTransform(&matRotate);

		g_pSprite->Draw(texCharacters,&rc,NULL, NULL, 0xFFFFFFFF);

		g_pSprite->SetTransform(&preChange);
		///////////////

		///// SKELETON ANTIGUO
		/*g_pSprite->Draw(texCharacters,&rc,NULL, 
						&D3DXVECTOR3(float(posx),float(posy),0.0f), 
						0xFFFFFFFF);*/
	}
	Skeleton->GetRectRadar(&rc,&posx,&posy);
	g_pSprite->Draw(texTiles,&rc,NULL, 
					&D3DXVECTOR3(float(posx),float(posy),0.0f), 
					0xFFFFFFFF);
	
	//Draw Fire
	//if(Critter->GetShooting())
	//{
	//	if(Critter->IsFiring())
	//	{
	//		//Advance animation & draw
	//		Critter->GetRectShoot(&rc,&posx,&posy,Scene);
	//		g_pSprite->Draw(texCharacters,&rc,NULL, 
	//						&D3DXVECTOR3(float(posx),float(posy),0.0f), 
	//						0xFFFFFFFF);
	//	}
	//	else
	//	{
	//		//Advance animation
	//		Critter->GetRectShoot(&rc,&posx,&posy,Scene);
	//	}
	//}
	return true;
}

bool cGraphicsLayer::DrawMouse()
{
	cMouse* Mouse = cInputLayer::GetInstance()->GetMouse();
	RECT rc;
	int mx,my,posx,posy;

	//Mouse selection box
	Mouse->GetPosition(&mx,&my);

	if(Mouse->GetSelection()==SELECT_SCENE)
	{
		int sx,sy;
		Mouse->GetSelectionPoint(&sx,&sy);
		SetRect(&rc,sx,sy,mx,my);
		DrawRect(rc,0x0000ff00);
	}

	//Mouse
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		
		Mouse->GetRect(&rc,&posx,&posy);
		HRESULT hr = g_pSprite->Draw(texMouse,&rc,NULL,&D3DXVECTOR3(float(mx+posx),float(my+posy),0.0f),0xFFFFFFFF);
		if(FAILED(hr))
		{
			cLog *Log = cLog::Instance();
			Log->Error(hr,"mouse pointer");
			return false;
		}

	g_pSprite->End();

	return true;
}

bool cGraphicsLayer::DrawRect(RECT rc, D3DCOLOR color)
{
	RECT rect;
	int xo,yo,xf,yf;

	if((rc.left==rc.right)&&(rc.top==rc.bottom)) return false;

	if(rc.left < rc.right)
	{
		xo = rc.left;	xf = rc.right;
	}
	else
	{
		xo = rc.right;	xf = rc.left;
	}
	if(rc.top < rc.bottom)
	{
		yo = rc.top;	yf = rc.bottom;
	}
	else
	{
		yo = rc.bottom;	yf = rc.top;
	}

	//Top
	SetRect(&rect,xo,yo,xf+1,yo+1);
	g_pD3DDevice->Clear(1,(D3DRECT *)&rect,D3DCLEAR_TARGET,color,1.0f,0);
	//Bottom
	SetRect(&rect,xo,yf,xf,yf+1);
	g_pD3DDevice->Clear(1,(D3DRECT *)&rect,D3DCLEAR_TARGET,color,1.0f,0);
	//Left
	SetRect(&rect,xo,yo,xo+1,yf+1);
	g_pD3DDevice->Clear(1,(D3DRECT *)&rect,D3DCLEAR_TARGET,color,1.0f,0);
	//Right
	SetRect(&rect,xf,yo,xf+1,yf+1);
	g_pD3DDevice->Clear(1,(D3DRECT *)&rect,D3DCLEAR_TARGET,color,1.0f,0);
	
	return true;
}
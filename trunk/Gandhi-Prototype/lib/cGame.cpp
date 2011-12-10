
#include "cGame.h"
#include "cLog.h"
#include "cGSMenu.h"
#include "cGSIngame.h"
//#include "cGSGameOver.h"

cGame* cGame::instance = NULL;

cGame::cGame() {}
cGame::~cGame()
{
	//EFG: Eliminamos la memoria dinámica
	if (Graphics != NULL)
	{
		delete Graphics;
		Graphics = NULL;
	}
	if (Input != NULL)
	{
		delete Input;
		Input = NULL;
	}
	if (Sound != NULL)
	{
		delete Sound;
		Sound = NULL;
	}
	if (Scene != NULL)
	{
		delete Scene;
		Scene = NULL;
	}
	if (HUD != NULL)
	{
		delete HUD;
		HUD = NULL;
	}
	if (State != NULL)
	{
		delete State;
		State = NULL;
	}
	if (Hero != NULL)
	{
		delete Hero;
		Hero = NULL;
	}
}

cGame* cGame::GetInstance()
{
	if (instance == NULL)
	{
		instance = new cGame();
	}
	
	return instance;
}

bool cGame::Init(HWND hWnd,HINSTANCE hInst,bool exclusive)
{
	bool res;
	
	cLog *Log = cLog::Instance();
	
	// EFG: Instanciamos gráficos, sonido e input
	Graphics = cGraphicsLayer::GetInstance();
	Sound = cSound::GetInstance();
	Input = cInputLayer::GetInstance();

	// EFG: Creamos la escena y el HUD
	Scene = new cScene();

	// EFG: Creamos el heroe... y el enemigo de momento
	//Hero = new cHero();
	//Enemies.push_back(cEnemy());
	//Item = new cItem();

	// Arnau: Comentado para debugar más rápido
	// EFG: Iniciamos el estado menú
	//State = new cGSMenu();
	State = new cGSIngame(); // Arnau: borrar en beta

	State->Enter();

	res = Graphics->Init(hWnd, !exclusive); //fullscreen = !exclusive
	if(!res)
	{
		Log->Msg("Error initializing Graphics!");
		return false;
	}

	res = Input->Init(hInst,hWnd,exclusive,USE_MOUSE|USE_KEYBOARD);
	if(!res)
	{
		Log->Msg("Error initializing Input!");
		return false;
	}
	Input->SetMousePosition(SCREEN_RES_X >> 1,SCREEN_RES_Y >> 1);

	Graphics->LoadData();

	Scene->LoadMap("media/map.txt");

	return true;
}

void cGame::Finalize()
{
	Graphics->UnLoadData();
	Graphics->Finalize();
	Input->UnacquireAll();
	Input->Finalize();
	
	
}

bool cGame::Loop()
{
	bool res;

	//Input
	res = LoopInput();
	if(!res) return false;
	
	//Process
	res = LoopProcess();
	if(!res) return false;

	//Output
	res = LoopOutput();
	if(!res) return false;
	
	return true;
}

bool cGame::LoopInput()
{
	bool res;
	cLog *Log = cLog::Instance();

	res = Input->Read();
	if(!res)
	{
		Log->Msg("Error reading Input!");
		//return false; // Arnau: comentado porqué al perder focus devolvía false y cerraba la aplicación el joputa
	}
	return true;
}

bool cGame::LoopProcess()
{
	return State->Process();
}

bool cGame::LoopOutput()
{
	bool res;
	res = Render();
	return res;
}

bool cGame::Render()
{
	bool res;

	// EFG: El juego llama al método pintar del estado
	// y el estado, en función de cuál sea, le dirá a la
	// los gráficos que pinten una cosa u otra
	res = State->Render();

	return res;
}

void cGame::ProcessKeyboard() {
	cKeyboard *Keyboard;
	Keyboard = Input->GetKeyboard();

	if(Keyboard->KeyDown(DIK_W) || Keyboard->KeyDown(DIK_UP)) {
		if(Hero->Move(DIRUP)) Scene->Move(DIRUP);
	}
	else if(Keyboard->KeyDown(DIK_S) || Keyboard->KeyDown(DIK_DOWN)) {
		if(Hero->Move(DIRDOWN)) Scene->Move(DIRDOWN);
	}
	if(Keyboard->KeyDown(DIK_D) || Keyboard->KeyDown(DIK_RIGHT)) {
		if(Hero->Move(DIRRIGHT)) Scene->Move(DIRRIGHT);
	}
	else if(Keyboard->KeyDown(DIK_A) || Keyboard->KeyDown(DIK_LEFT)) {
		if(Hero->Move(DIRLEFT)) Scene->Move(DIRLEFT);
	}
}

void cGame::ProcessCollisions()
{
	RECT hr;
	Hero->GetWorldRect(&hr);
	
	list<cItem*>::iterator it = Items.begin();
	while(it != Items.end()) {
		RECT ir;
		cItem* item = *it;
		item->GetWorldRect(&ir);
		if(intersects(&hr, &ir)) {
			item->Use();
			it = Items.erase(it);
		}
		else it++;
	}

	list<cBullet*>::iterator hit = HeroBullets.begin();
	while(hit != HeroBullets.end()) {
		RECT br;
		cBullet* bullet = *hit;
		bullet->GetWorldRect(&br);
		cEnemy* enemy = intersectsWithEnemy(&br);
		if(enemy != NULL) {
			if(enemy->Hit(bullet->GetDamage())) {
				Enemies.remove(enemy);
			}
			hit = HeroBullets.erase(hit);
		}
		else hit++;
	}

	hit = EnemyBullets.begin();
	while(hit != EnemyBullets.end()) {
		RECT br;
		cBullet* bullet = *hit;
		bullet->GetWorldRect(&br);
		if(intersects(&hr, &br)) {
			if(Hero->Hit(bullet->GetDamage())) {
				// TODO: Game Over!
				//ChangeState(new cGSGameOver());
			}
			hit = EnemyBullets.erase(hit);
		}
		else hit++;
	}
}

void cGame::ProcessEnemies()
{
	for(list<cEnemy*>::iterator it = Enemies.begin(); it != Enemies.end(); it++) {
		cEnemy* enemy = *it;
		enemy->Move();
	}

	list<cBullet*>::iterator hit = EnemyBullets.begin();
	while(hit != EnemyBullets.end()) {
		cBullet* bullet = *hit;
		if(!bullet->Move()) {
			hit = EnemyBullets.erase(hit);
		}
		else hit++;
	}

	hit = HeroBullets.begin();
	while(hit != HeroBullets.end()) {
		cBullet* bullet = *hit;
		if(!bullet->Move()) {
			hit = HeroBullets.erase(hit);
		}
		else hit++;
	}
}

void cGame::ProcessOrder()
{
	int mx, my;
	cMouse *Mouse;
	int b4pointer;

	Mouse = Input->GetMouse();
	b4pointer = Mouse->GetPointer();
	//Mouse->Read(); //Arnau: comentado porqué tampoco hace nada...
	Mouse->GetPosition(&mx,&my);

	ProcessKeyboard();
	ProcessEnemies();
	ProcessCollisions();

	if(Mouse->ButtonDown(LEFT))
	{
		Mouse->SetPointer(NORMAL);
		
		if(Mouse->In(SCENE_Xo,SCENE_Yo,SCENE_Xf,SCENE_Yf))
		{
			// EFG: Mouse dentro de la escena
			Hero->ShootAt(mx, my);

			
		}
	}
	else if(Mouse->ButtonUp(LEFT))
	{
		Mouse->SetSelection(SELECT_NOTHING);

		//Mouse over Enemy
		/* EFG: Esto puede servir de algo
		Skeleton.GetCell(&cx,&cy);
		if(Mouse->InCell(&Scene,cx,cy))
		{
			Mouse->SetPointer(ATTACK);
		}
		else if(Mouse->In(s,SCENE_Yo,SCENE_Xf,SCENE_Yf-s))
		{
			//Critter selected pointing, where to move
			if(Critter.GetSelected())	Mouse->SetPointer(MOVE);
			//Critter selected but mouse out map
			else						Mouse->SetPointer(NORMAL);
		}
		else
		{	
			//Arrow mouse pointers to move through scene
			if	   (Mouse->In(             s,             s,SCREEN_RES_X-s,SCREEN_RES_Y-s)) Mouse->SetPointer(NORMAL);
			else if(Mouse->In(             s,             0,SCREEN_RES_X-s,             s)) Mouse->SetPointer(MN);
			else if(Mouse->In(             s,SCREEN_RES_Y-s,SCREEN_RES_X-s,  SCREEN_RES_Y)) Mouse->SetPointer(MS);
			else if(Mouse->In(SCREEN_RES_X-s,             s,  SCREEN_RES_X,SCREEN_RES_Y-s)) Mouse->SetPointer(ME);
			else if(Mouse->In(             0,             s,             s,SCREEN_RES_Y-s)) Mouse->SetPointer(MO);
			else if(Mouse->In(             0,             0,             s,             s)) Mouse->SetPointer(MNO);
			else if(Mouse->In(             0,SCREEN_RES_Y-s,             s,  SCREEN_RES_Y)) Mouse->SetPointer(MSO);
			else if(Mouse->In(SCREEN_RES_X-s,             0,  SCREEN_RES_X,             s)) Mouse->SetPointer(MNE);
			else if(Mouse->In(SCREEN_RES_X-s,SCREEN_RES_Y-s,  SCREEN_RES_X,  SCREEN_RES_Y)) Mouse->SetPointer(MSE);
			else																			Mouse->SetPointer(NORMAL);

			p = Mouse->GetPointer();
			if((p>=MN)&&(p<=MSO))	Scene.Move(p);
		}*/
	}
	if(Mouse->ButtonDown(RIGHT))
	{
		//EFG: Segundo ataque?
	}

	//if(b4pointer!=Mouse->GetPointer()) Mouse->InitAnim();
}

bool cGame::ChangeState(cGameState* newState)
{
	// EFG: Salimos del estado actual y lo borramos
	if (State != NULL)
	{
		State->Exit();
		delete State;
		State = NULL;
	}
	// EFG: Hacemos del nuevo estado el estado actual y entramos en el
	if (newState != NULL)
	{
		State = newState;
		State->Enter();
		return true;
	}
	else
	{
		return false;
	}
}

void cGame::addEnemy(int type, int cx, int cy)
{
	Enemies.push_back(new cEnemy(type, cx, cy));
}

void cGame::addItem(int type, int cx, int cy)
{
	Items.push_back(new cItem(type, cx, cy));
}

void cGame::addHero(int cx, int cy)
{
	Hero = new cHero(cx, cy);
}

void cGame::addEnemyBullet( int type, int x, int y, int vx, int vy )
{
	EnemyBullets.push_back(new cBullet(type, x, y, vx, vy));
}

void cGame::addHeroBullet( int type, int x, int y, int vx, int vy )
{
	HeroBullets.push_back(new cBullet(type, x, y, vx, vy));
}

bool cGame::intersects(RECT *r1, RECT *r2)
{
	return !(r1->left > r2->right || r1->right < r2->left ||
		r1->top > r2->bottom || r1->bottom < r2->top);
}

cEnemy* cGame::intersectsWithEnemy(RECT *r)
{
	return NULL; //debug
	//if(Enemies == NULL) return NULL;
	for(list<cEnemy*>::iterator it = Enemies.begin(); it != Enemies.end(); it++) {
		RECT er;
		cEnemy* enemy = *it;
		enemy->GetWorldRect(&er);
		if(intersects(r, &er)) return enemy;
	}
	return NULL;
}


#include "cGame.h"
#include "cLog.h"
#include "cGSMenu.h"
#include "cGSIngame.h"
#include "cGSGameOver.h"
#include "cGSGameEnd.h"

cGame* cGame::instance = NULL;

cGame::cGame() {
	State = NULL;
	gameEnd = new cGSGameEnd();
	gameOver = new cGSGameOver();
	inGame = new cGSIngame();
	menu = new cGSMenu();
}

cGame::~cGame()
{
	//EFG: Eliminamos la memoria din�mica
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
	
	GamePoints = 0;
	rumble = 0;
	cLog *Log = cLog::Instance();
	
	// EFG: Instanciamos gr�ficos, sonido e input
	Graphics = cGraphicsLayer::GetInstance();
	Sound = cSound::GetInstance();
	Input = cInputLayer::GetInstance();

	// EFG: Creamos la escena y el HUD
	Scene = new cScene();
	HUD = new cHUD();
	// EFG: Creamos el heroe... y el enemigo de momento
	Hero = new cHero();
	//Enemies.push_back(cEnemy());
	//Item = new cItem();

	// Arnau: Comentado para debugar m�s r�pido
	// EFG: Iniciamos el estado men�
	ChangeState(menu);
	//State = new cGSIngame(); // Arnau: borrar en beta

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

	//Scene->LoadMap("media/map.txt");


	// Cargamos efectos de sonido
	Sound->inicializarAudio();
	Sound->cargarCancion("media/sounds/Kalimba.mp3");
	Sound->cargarEfecto("media/sounds/stepMetal1.wav", "pasos");
	Sound->cargarEfecto("media/sounds/hurt3.wav", "hit");
	Sound->cargarEfecto("media/sounds/forceField.wav", "shield");
	Sound->cargarEfecto("media/sounds/minigun.wav", "w1");
	Sound->cargarEfecto("media/sounds/railgun.wav", "w2");
	Sound->cargarEfecto("media/sounds/plasma.wav", "w3");
	Sound->cargarEfecto("media/sounds/grenadeExplode.wav", "explo");
	Sound->cargarEfecto("media/sounds/unstoppable.wav", "end");
	Sound->cargarEfecto("media/sounds/humiliation.wav", "over");
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
		//return false; // Arnau: comentado porqu� al perder focus devolv�a false y cerraba la aplicaci�n el joputa
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

	// EFG: El juego llama al m�todo pintar del estado
	// y el estado, en funci�n de cu�l sea, le dir� a la
	// los gr�ficos que pinten una cosa u otra
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

	if (Keyboard->KeyUp(DIK_W) &&
		Keyboard->KeyUp(DIK_A) &&
		Keyboard->KeyUp(DIK_S) &&
		Keyboard->KeyUp(DIK_D))
	{
		Hero->Move(DIRNONE);
	}

	if (Keyboard->KeyDown(DIK_SPACE))
	{
		State->Process();
	}
}

void cGame::ProcessCollisions()
{
	RECT hr;
	Hero->GetWorldRect(&hr);
	
	// CON LOS ITEMS
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

	// CON LAS BALAS DEL HEROE
	list<cBullet*>::iterator hit = HeroBullets.begin();
	while(hit != HeroBullets.end()) {
		RECT br;
		cBullet* bullet = *hit;
		bullet->GetWorldRect(&br);
		cEnemy* enemy = intersectsWithEnemy(&br);
		if(enemy != NULL) {
			if(enemy->Hit(bullet->GetDamage())) {
				enemy->Die();
				Enemies.remove(enemy);
			}
			hit = HeroBullets.erase(hit);
		}
		else hit++;
	}

	// CON LAS BALAS ENEMIGAS
	hit = EnemyBullets.begin();
	while(hit != EnemyBullets.end()) {
		RECT br;
		cBullet* bullet = *hit;
		bullet->GetWorldRect(&br);
		if(intersects(&hr, &br)) {
			if(Hero->Hit(bullet->GetDamage()/*>>1*/)) { //>>1 ajuste de dificultad
				ChangeState(gameOver);
			}
			hit = EnemyBullets.erase(hit);
		}
		else hit++;
	}
}

void cGame::ProcessEnemies()
{
	list<cEnemy*>::iterator it = StalkingEnemies.begin();
	while(it != StalkingEnemies.end()) {
		cEnemy* enemy = *it;
		int cx, cy;
		enemy->GetCell(&cx, &cy);
		if(Scene->Visible(cx, cy)) {
			list<cEnemy*>::iterator tmpit = it;
			it++;
			Enemies.splice(Enemies.begin(), StalkingEnemies, tmpit);
		}
		else it++;
	}

	for(list<cEnemy*>::iterator it = Enemies.begin(); it != Enemies.end(); it++) {
		cEnemy* enemy = *it;
		enemy->update();
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
		//delete State;
		//State = NULL;
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

void cGame::addStalkingEnemy(int type, int cx, int cy)
{
	StalkingEnemies.push_back(new cEnemy(type, cx, cy));
}

void cGame::addItem(int type, int posx, int posy)
{
	Items.push_back(new cItem(type, posx, posy));
}

void cGame::addEnemyBullet( int type, int x, int y, int vx, int vy )
{
	EnemyBullets.push_back(new cBullet(type, x, y, vx, vy));

	if(EnemyBullets.size()%2 == 0 && Scene->Visible(x>>TILE_W_SHIFT, y>>TILE_W_SHIFT)) {
		switch (type)
		{
		case BULL_1:
			Sound->playEfecto("w1");
			break;
		case BULL_2:
			Sound->playEfecto("w2");
			break;
		case BULL_3:
			Sound->playEfecto("w3");
			break;
		}
	}
}

void cGame::addHeroBullet( int type, int x, int y, int vx, int vy )
{
	HeroBullets.push_back(new cBullet(type, x, y, vx, vy));

	switch (type)
	{
	case BULL_1:
		Sound->playEfecto("w1");
		break;
	case BULL_2:
		Sound->playEfecto("w2");
		break;
	case BULL_3:
		Sound->playEfecto("w3");
		break;
	}
}

bool cGame::intersects(RECT *r1, RECT *r2)
{
	return !(r1->left > r2->right || r1->right < r2->left ||
		r1->top > r2->bottom || r1->bottom < r2->top);
}

cEnemy* cGame::intersectsWithEnemy(RECT *r)
{
	return intersectsWithEnemy(r, NULL);
}

cEnemy* cGame::intersectsWithEnemy(RECT *r, cEnemy *self)
{
	for(list<cEnemy*>::iterator it = Enemies.begin(); it != Enemies.end(); it++) {
		RECT er;
		cEnemy* enemy = *it;
		if(enemy == self) continue;
		enemy->GetWorldRect(&er);
		if(intersects(r, &er)) return enemy;
	}
	return NULL;
}

void cGame::addLevelEnd( int cx, int cy )
{
	Items.push_back(new cItem(IT_END_CAR, cx<<TILE_W_SHIFT, cy<<TILE_W_SHIFT));
}


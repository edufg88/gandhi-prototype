
#include "cGame.h"
#include "cLog.h"
#include "cGSMenu.h"

cGame* cGame::instance = NULL;

cGame::cGame() {}
cGame::~cGame(){}

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
	
	// EFG: Instanciamos gr�ficos, sonido e input
	Graphics = cGraphicsLayer::GetInstance();
	Sound = cSound::GetInstance();
	Input = cInputLayer::GetInstance();

	// EFG: Iniciamos el estado men�
	State = new cGSMenu();
	State->Enter();

	res = Graphics->Init(hWnd);
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

	//EFG: Scene.LoadMap("map.txt");

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
		return false;
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

void cGame::ProcessOrder()
{
	cMouse *Mouse;
	int mx,my,msx,msy,p,cx,cy,x,y;
	int s=5; //marge for directional pointers
	int xo,xf,yo,yf;
	int b4pointer;

	Mouse = Input->GetMouse();
	b4pointer = Mouse->GetPointer();
	Mouse->GetPosition(&mx,&my);

	if(Mouse->ButtonDown(LEFT))
	{
		Mouse->SetPointer(NORMAL);
		
		if(Mouse->In(SCENE_Xo,SCENE_Yo,SCENE_Xf,SCENE_Yf))
		{
			if(Mouse->GetSelection()!=SELECT_SCENE)
			{
				//Select movement/attack
				if(Critter.GetSelected())
				{
					//Attack
					Skeleton.GetCell(&cx,&cy);
					if(Mouse->InCell(&Scene,cx,cy))
					{
						if(!Critter.GetShooting())
							Critter.GoToEnemy(Scene.cx+cx,Scene.cx+cy);
					}
					//Movement
					else
					{
						Mouse->GetCell(&cx,&cy);
						Critter.GoToCell(Scene.cx+cx,Scene.cy+cy);
					}
				}
				//Begin selection
				else
				{
					Mouse->SetSelection(SELECT_SCENE);
					Mouse->SetSelectionPoint(mx,my);
				}
			}
		}
		else if(Mouse->In(RADAR_Xo,RADAR_Yo,RADAR_Xf,RADAR_Yf))
		{
			if(Critter.GetSelected())
			{
				int radar_cell_x = (mx-RADAR_Xo) >> 2, //[672..799]/4=[0..31]
					radar_cell_y = (my-RADAR_Yo) >> 2; //[ 60..187]/4=[0..31]

				Critter.GoToCell(radar_cell_x,radar_cell_y);
			}
			else
			{
				Mouse->SetSelection(SELECT_RADAR);
				Scene.MoveByRadar(mx,my);
			}
		}
	}
	else if(Mouse->ButtonUp(LEFT))
	{
		if(Mouse->GetSelection()==SELECT_SCENE)
		{
			Mouse->GetSelectionPoint(&msx,&msy);

			xo = min(msx,mx)+(Scene.cx<<5)-SCENE_Xo;
			xf = max(msx,mx)+(Scene.cx<<5)-SCENE_Xo;
			yo = min(msy,my)+(Scene.cy<<5)-SCENE_Yo,
			yf = max(msy,my)+(Scene.cy<<5)-SCENE_Yo;
			
			Critter.GetPosition(&x,&y);
			if((xo<(x+32))&&(xf>=x)&&(yo<(y+32))&&(yf>=y))
				Critter.SetSelected(true);
		}
		Mouse->SetSelection(SELECT_NOTHING);

		//Mouse over Critter
		Critter.GetCell(&cx,&cy);
		if(Mouse->InCell(&Scene,cx,cy))
		{
			Mouse->SetPointer(SELECT);
			return;
		}
		//Mouse over Enemy
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
		else if(Mouse->In(RADAR_Xo,RADAR_Yo,RADAR_Xf,RADAR_Yf))
		{
			//Critter selected pointing, where to move trough radar
			if(Critter.GetSelected())	Mouse->SetPointer(MOVE);
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
		}
	}
	if(Mouse->ButtonDown(RIGHT))
	{
		if(Critter.GetSelected())
		{
			Critter.SetSelected(false);
			Mouse->SetPointer(NORMAL);
		}
	}

	if(b4pointer!=Mouse->GetPointer()) Mouse->InitAnim();
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
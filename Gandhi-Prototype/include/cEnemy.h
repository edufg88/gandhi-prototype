#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <windows.h>

class cScene;

class cEnemy
{
	public:
		cEnemy(void);
		virtual ~cEnemy(void);

		void GetRect(RECT *rc,int *posx,int *posy,cScene *Scene);

		void SetPosition(int posx,int posy);
		void GetPosition(int *posx,int *posy);
		void SetCell(int cellx,int celly);
		void GetCell(int *cellx,int *celly);

	private:
		int x,y;		//Position in total map
		int cx,cy;		//Cell position in total map
};

#endif
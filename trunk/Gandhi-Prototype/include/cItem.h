#ifndef __ITEM_H__
#define __ITEM_H__

#include <windows.h>

#define ITEM_WIDTH 16
#define ITEM_HEIGHT 16

#define NUM_ITEMS 5
#define IT_LIFE 0
#define IT_SHIELD 1
#define IT_WEAPON_1 2
#define IT_WEAPON_2 3
#define IT_WEAPON_3 4

class cScene;

class cItem
{
	public:
		cItem(int type, int posx, int posy);

		virtual ~cItem(void);

		void GetRect(RECT *rc,int *posx,int *posy,cScene *Scene);

		void SetPosition(int posx,int posy);
		void GetPosition(int *posx,int *posy);
		void SetCell(int cellx,int celly);
		void GetCell(int *cellx,int *celly);

		void GetWorldRect(RECT *rc);
		void Use();

	private:
		int x,y;		//Position in total map
		//int cx,cy;		//Cell position in total map
		int type;
};

#endif
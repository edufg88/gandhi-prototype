#ifndef __ITEM_H__
#define __ITEM_H__

#include <windows.h>

class cScene;

class cItem
{
	public:
		cItem(void);
		// EFG: Si hacemos más de 1 ítem podemos hacer la clase abstracta.
		virtual ~cItem(void);

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
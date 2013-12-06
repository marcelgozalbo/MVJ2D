
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "cInputLayer.h"

class cKeyboard
{
public:
	cKeyboard(LPDIRECTINPUT8 pDI, HWND hwnd);
	~cKeyboard();

	bool KeyDown(int key);
	bool KeyUp(int key);
	bool KeyUpDown(int key);
	bool KeyDownUp(int key);
	void KeyClear(int key);

	bool Read();
	void Clear();
	
	bool Acquire();
	bool Unacquire();

private:
	LPDIRECTINPUTDEVICE8 m_pDIDev;

	char m_keys[256];
	char m_last_keys[256];
};

#endif 
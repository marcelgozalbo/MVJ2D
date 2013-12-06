
#include "cInputLayer.h"
#include "cMouse.h"
#include "cKeyboard.h"
#include "cLog.h"

/************************************************************************
Construction and destruction functions
************************************************************************/
cInputLayer::cInputLayer()
{
	m_pDI = NULL;
	m_pKeyboard = NULL;
	m_pMouse = NULL;
}
cInputLayer::~cInputLayer()
{
	Finalize();
}

/************************************************************************
cInput::Initialize()

Initializes the input system. 
isExclusive set to true for exclusive mouse access
USE_KEYBOARD and USE_MOUSE are flags
************************************************************************/
bool cInputLayer::Init(HINSTANCE hInst, HWND hWnd, bool isExclusive, DWORD flags)
{
	cLog *Log = cLog::Instance();
	HRESULT hr;

	// create DirectInput (DI) object
	hr = DirectInput8Create(hInst,
							DIRECTINPUT_VERSION,	// defined in dinput.h
							IID_IDirectInput8,		// identifirer for desired DirectInput interface
							(void **)&m_pDI,		// pointer to variable that will point to requested 
													// interface, our main DirectObject for input
							NULL);					// for aggregration. unused so set to NULL
	if(FAILED(hr))
	{
		Log->Error(hr,"Creating DI object");
		return false;
	}

	if( flags & USE_KEYBOARD)
	{
		m_pKeyboard = new cKeyboard(m_pDI, hWnd);
		if(m_pKeyboard == NULL)
		{
			Log->Msg("Error creating keyboard object!");
			return false;
		}
	}

	if( flags & USE_MOUSE)
	{
		m_pMouse = new cMouse(m_pDI, hWnd, isExclusive);
		if(m_pMouse == NULL)
		{
			Log->Msg("Error creating mouse object!");
			return false;
		}
	}

	return true;
}



/************************************************************************
cInput::Finalize()

Releases objects, frees memory
************************************************************************/
bool cInputLayer::Finalize()
{
	UnacquireAll();
	if(m_pKeyboard)
	{
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}
	if (m_pMouse)
	{
		delete m_pMouse;
		m_pMouse = NULL;
	}
	if(m_pDI)
	{
		m_pDI->Release();
		m_pDI = NULL;
	}
	return true;
}

/************************************************************************
cInput::Read()

Queries current state of devices
*************************************************************************/
bool cInputLayer::Read()
{
	bool res=true;
	cLog *Log = cLog::Instance();

	if(m_pKeyboard)
	{
		res = m_pKeyboard->Read();
		if(!res)
		{
			//Log->Msg("Error reading from keyboard device!");
			return false;
		}
	}
	if(m_pMouse)
	{
		res = m_pMouse->Read();
		if(!res)
		{
			//Log->Msg("Error reading from mouse device!");
			return false;
		}
	}
	return res;
}


/************************************************************************
 cInput::AcquireAll()

 Makes sure all input devices are acquired
*************************************************************************/
void cInputLayer::AcquireAll()
{
  if (m_pKeyboard)
    m_pKeyboard->Acquire();
  if (m_pMouse)
    m_pMouse->Acquire();
} 

/*************************************************************************
 cInput::UnacquireAll()

 Unacquires all devices
**************************************************************************/
void cInputLayer::UnacquireAll()
{
  if (m_pKeyboard)
    m_pKeyboard->Unacquire();
  if (m_pMouse)
    m_pMouse->Unacquire();
} 

/*************************************************************************
 Device queries
**************************************************************************/
cKeyboard* cInputLayer::GetKeyboard()
{
	return m_pKeyboard;
}
cMouse* cInputLayer::GetMouse()
{
	return m_pMouse;
}
bool cInputLayer::KeyDown(int key)
{
	return m_pKeyboard->KeyDown(key);
}
bool cInputLayer::KeyUp(int key)
{	
	return m_pKeyboard->KeyUp(key);
}
bool cInputLayer::KeyUpDown(int key)
{
	return (m_pKeyboard->KeyUpDown(key));

}
bool cInputLayer::KeyDownUp(int key)
{
	return (m_pKeyboard->KeyDownUp(key));
}
void cInputLayer::KeyClear(int key)
{
	return m_pKeyboard->KeyClear(key);
}
bool cInputLayer::ButtonDown(int button)
{
	if (!m_pMouse)
		return false;

	return m_pMouse->ButtonDown(button);
}
bool cInputLayer::ButtonUp(int button)
{
	if (!m_pMouse)
		return false;

	return m_pMouse->ButtonUp(button);
}
void cInputLayer::GetMouseMovement(int *dx, int *dy)
{
	if (!m_pMouse)
		return;

	m_pMouse->GetMovement(dx, dy);
}
int	 cInputLayer::GetMouseWheelMovement()
{
	if (!m_pMouse)
		return 0;

	return m_pMouse->GetWheelMovement();
}
void cInputLayer::SetMousePosition(int xo, int yo)
{
	if (!m_pMouse)
		return;

	m_pMouse->SetPosition(xo,yo);
}
void cInputLayer::GetMousePosition(int *xpos, int *ypos)
{
	if (!m_pMouse)
		return;

	m_pMouse->GetPosition(xpos,ypos);
}

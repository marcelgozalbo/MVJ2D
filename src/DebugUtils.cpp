#include "DebugUtils.h"

void leakDetectionInit()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif
}

void leakDetectionStop()
{
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
}

void breakOnAllocation(int _allocation)
{
#ifdef _DEBUG
	_CrtSetBreakAlloc(_allocation);
#endif
}


#ifndef MPV2D_DEBUG_UTILS_H_
#define MPV2D_DEBUG_UTILS_H_

#ifdef _DEBUG

// activem el detector de leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// macro per fer servir l'operador new sobreescrit per afegir fitxer i linia
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif

#endif

void leakDetectionInit();
void leakDetectionStop();
void breakOnAllocation(int _allocation);

#endif


#ifndef __LOG_H__
#define __LOG_H__

#pragma comment(lib,"dxerr9.lib")

#include <windows.h>
#include <string>

class cLog
{
public: 
    static cLog* Instance();
	static void Msg(char *msg);
	static void Msg(const std::string& aMsg);
	static void Error(HRESULT hr, char *msg);

private:
    static cLog* _instance;
};

#endif
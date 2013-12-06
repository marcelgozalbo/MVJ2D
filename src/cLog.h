
#ifndef __LOG_H__
#define __LOG_H__

#pragma comment(lib,"dxerr9.lib")

#include <windows.h>
#include <string>

class cLog
{
public: 
    static cLog* Instance();
	static void Release();
	static void Msg(const char *format, ...);
	static void Msg(const std::string& aMsg);
	static void Error(HRESULT hr, char *msg);
	static void Clear();

private:
    static cLog* _instance;
};

#define LOG(text) cLog::Instance()->Msg(text);

#endif

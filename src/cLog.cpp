#include "cLog.h"
#include <dxerr9.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>


cLog* cLog::_instance = 0;

cLog* cLog::Instance()
{
	FILE *f;

    if (_instance == 0)
	{
        _instance = new cLog;
		
		errno_t err=fopen_s(&f, "log.txt","w");
		if (err)
		{
			std::cout << "Open file log.txt failed with errno: " << err << std::endl;
			return nullptr;
		}
		fclose(f);
    }
    return _instance;
}

void cLog::Release()
{
	if (_instance)
	{
		delete _instance;
	}
}

/**************************************************************************
	msg
**************************************************************************/
void cLog::Msg(const char *format, ...)
{
	static const unsigned int LOG_MAX_SIZE = 1024;
	char dest[LOG_MAX_SIZE];

	va_list argptr;
	va_start(argptr, format);
	vsprintf_s(dest, format, argptr);
	va_end(argptr);
	printf(dest);

	FILE *f;
	char s[256];

	ZeroMemory(s,sizeof(s));

	sprintf_s(s,"%s\n", dest);
	errno_t err = fopen_s(&f, "log.txt", "a+");
	if (err)
	{
		std::cout << "Open file log.txt failed with errno: " << err << std::endl;
		return;
	}
	fwrite(s,sizeof(char),strlen(s),f);
	fclose(f);
}

void cLog::Msg(const std::string& aMsg)
{
	FILE *f;
	char s[256];

	ZeroMemory(s, sizeof(s));

	sprintf_s(s, "%s\n", aMsg.c_str());
	errno_t err = fopen_s(&f, "log.txt", "a+");
	if (err)
	{
		std::cout << "Open file log.txt failed with errno: " << err << std::endl;
		return;
	}
	fwrite(s, sizeof(char), strlen(s), f);
	fclose(f);
}

/**************************************************************************
	Error: msg
	Code: hr
	Description: desc(hr)
**************************************************************************/
void cLog::Error(HRESULT hr, char *msg)
{
	FILE *f;
	char s[256];

	ZeroMemory(s,sizeof(s));

	sprintf_s(s, "Error: %s\n", msg);
	sprintf_s(s, "%sCode: %s\n", s, (char *)DXGetErrorString9(hr));
	sprintf_s(s, "%sDescription: %s\n", s, DXGetErrorDescription9(hr));
	
	errno_t err = fopen_s(&f, "log.txt", "a+");
	if (err)
	{
		std::cout << "Open file log.txt failed with errno: " << err << std::endl;
		return;
	}
	fwrite(s,sizeof(char),strlen(s),f);
	fclose(f);
}

void cLog::Clear()
{
	FILE *f;

	errno_t err = fopen_s(&f, "log.txt", "w");
	if (err)
	{
		std::cout << "Open file log.txt failed with errno: " << err << std::endl;
		return;
	}
	fclose(f);
}

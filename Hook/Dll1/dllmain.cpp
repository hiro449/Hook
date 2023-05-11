// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include <Windows.h>
#include<stdio.h>

typedef unsigned __int64 QWORD;

void WINAPI function() {//呼ばれる奴

    MessageBoxA(NULL, "detoured!!", "success", MB_OK);
}

bool WINAPI Hook(void* tarGet, void* myfunc, int lenHook) {//putの命令をmyfuncへ

    DWORD BeforePro;
    VirtualProtect(tarGet,lenHook, PAGE_EXECUTE_READWRITE, &BeforePro);

    //call <JMP.&puts>5
     //mov ecx5
     //mov rax, qword ptr ds : [<&Sleep>]7
     //call rax ↓2
    memset(tarGet, 0x90, lenHook);

    *(BYTE*)tarGet = 0x48;
    *((BYTE*)tarGet + 1) = 0xb8;//move rax
    *(QWORD*)((BYTE*)tarGet + 2) = (QWORD)myfunc; // mov rax, <myfuncAddr>
    //mov rax, <myfunc>
    //call rax
    *((BYTE*)tarGet + 10) = 0xff;
    *((BYTE*)tarGet + 11) = 0xd0;         // call rax

    DWORD AfterPro;
    VirtualProtect(tarGet, lenHook, BeforePro, &AfterPro);



    return 0;

}



DWORD WINAPI thread(void * a) {

    int lenHook = 12;//替える数
    DWORD callNumber = 0;//Hookのentrypoint
    
//reinterpret_cast<void*>(static_cast<DWORD_PTR>(callNumber)
    if (Hook(a, function, lenHook))
        MessageBoxA(NULL, "成功しました", "info", MB_OK);


    FreeLibraryAndExitThread((HMODULE)a, 0);
    return 0;

}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, thread, hModule, 0, 0);
        break;
    }
    return TRUE;
}


/*
HANDLE CreateSemaphoreA(
  [in, optional] LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  [in]           LONG                  lInitialCount,
  [in]           LONG                  lMaximumCount,
  [in, optional] LPCSTR                lpName
);


HANDLE OpenSemaphoreW(
  [in] DWORD   dwDesiredAccess,
  [in] BOOL    bInheritHandle,
  [in] LPCWSTR lpName
);

*/


#include<windows.h>
#include <iostream>
using namespace std;


int main16()
{
    HANDLE namedSemaphore = NULL;
    HANDLE unnamedSemaphore = NULL;
    unnamedSemaphore = CreateSemaphore(
        NULL,
        1,
        1,
        NULL
    );

    namedSemaphore = CreateSemaphore(
        NULL,
        1,
        1,
        L"MySemaphore"
    );

    if(namedSemaphore == NULL || unnamedSemaphore == NULL) {
        cout << "Semaphore creation failed with error number " << GetLastError() << endl;
        return 1;
    }
    cout << "Semaphores succesfully created" << endl;
    getchar();
    CloseHandle(namedSemaphore);
    CloseHandle(unnamedSemaphore);
    system("pause");
    return 0;
}
/*
BOOL ReleaseMutex(
  [in] HANDLE hMutex
);
DWORD WaitForSingleObject(
  [in] HANDLE hHandle,
  [in] DWORD  dwMilliseconds
);

DWORD WaitForMultipleObjects(
    [in] DWORD        nCount,
    [in] const HANDLE* lpHandles,
    [in] BOOL         bWaitAll,
    [in] DWORD        dwMilliseconds
);
*/

#include<windows.h>
#include <iostream>
using namespace std;

HANDLE hMutex; //Global mutex handle
int gcount = 0;
DWORD WINAPI ThreadFuncEven(LPVOID lpParam) {

    while (gcount < 10) {

        WaitForSingleObject(hMutex, INFINITE);
        if (gcount % 2 == 0) {
            cout << "Even - " << gcount++ << endl;
        }
        ReleaseMutex(hMutex);
    }
    return 0;
}

DWORD WINAPI ThreadFuncOdd(LPVOID lpParam) {

    while (gcount < 10) {

        WaitForSingleObject(hMutex, INFINITE);
        if (gcount % 2 != 0) {
            cout << "Odd - " << gcount++ << endl;
        }
        ReleaseMutex(hMutex);
    }
    return 0;
}
int main14()
{
    HANDLE hThread1 = NULL, hThread2 = NULL;
    hMutex = CreateMutex(
        NULL,
        FALSE,
        NULL);

    hThread1 = CreateThread(
        NULL,
        0,
        ThreadFuncEven,
        NULL,
        0,
        NULL
    );
    hThread2 = CreateThread(
        NULL,
        0,
        ThreadFuncOdd,
        NULL,
        0,
        NULL
    );
    if (hThread1 != NULL ) {
        CloseHandle(hThread1);
    }
    else {
        cout << "Error creating Thread with error " << GetLastError() << endl;
    }
    if (hThread2 != NULL) {
        CloseHandle(hThread2);
    }
    else {
        cout << "Error creating Thread with error " << GetLastError() << endl;
    }
    
    system("pause");
    return 0;
}
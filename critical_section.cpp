/*
* https://learn.microsoft.com/en-us/windows/win32/sync/critical-section-objects
* void EnterCriticalSection(
  [in, out] LPCRITICAL_SECTION lpCriticalSection
);
void LeaveCriticalSection(
  [in, out] LPCRITICAL_SECTION lpCriticalSection
);
void DeleteCriticalSection(
  [in, out] LPCRITICAL_SECTION lpCriticalSection
);
*/

#include<windows.h>
#include <iostream>
using namespace std;

int gcount1 = 1;
CRITICAL_SECTION cs;
DWORD WINAPI ThreadFuncEven1(LPVOID lpParam) {

   
    while (gcount1 < 10) {
        EnterCriticalSection(&cs);
        if (gcount1 % 2 == 0) {
            cout << "Even - " << gcount1++ << endl;
        }
        LeaveCriticalSection(&cs);
    }
    
    return 0;
}

DWORD WINAPI ThreadFuncOdd1(LPVOID lpParam) {

    
    while (gcount1 < 10) {
        EnterCriticalSection(&cs);
        if (gcount1 % 2 != 0) {
            cout << "Odd - " << gcount1++ << endl;
        }
        LeaveCriticalSection(&cs);
    }
    
    return 0;
}
int main29()
{
    cout << "Critical section" << endl;
    HANDLE hThread1 = NULL, hThread2 = NULL;
    //initialize the critical section
    InitializeCriticalSection(&cs);

    hThread1 = CreateThread(
        NULL,
        0,
        ThreadFuncEven1,
        NULL,
        0,
        NULL
    );
    hThread2 = CreateThread(
        NULL,
        0,
        ThreadFuncOdd1,
        NULL,
        0,
        NULL
    );
    if (hThread1 == NULL) {
        cout << "Error creating Thread with error " << GetLastError() << endl;
        return 1;
    }
   
    if (hThread2 == NULL) {
        cout << "Error creating Thread with error " << GetLastError() << endl;
        return 1;
    }
    cout << "Thread 1 and 2 succesfully created" << endl;
    //wait for signalled object
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    //delete the critical section
    DeleteCriticalSection(&cs);
    system("pause");
    return 0;
}
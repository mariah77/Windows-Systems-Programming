/*
HANDLE CreateEventA(
  [in, optional] LPSECURITY_ATTRIBUTES lpEventAttributes,
  [in]           BOOL                  bManualReset,
  [in]           BOOL                  bInitialState,
  [in, optional] LPCSTR                lpName
);
BOOL SetEvent(
  [in] HANDLE hEvent
)
https://learn.microsoft.com/en-us/windows/win32/sync/synchronization-object-security-and-access-rights
*/

#include<windows.h>
#include <iostream>
using namespace std;

HANDLE hEvent1 = NULL; //Global mutex handle

DWORD WINAPI ThreadFunc3(LPVOID lpParam) {

    HANDLE hOpenEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"MyEvent");
    if (hOpenEvent == FALSE) {
        cout << "Event can't be opened and error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Open event function is succesful" << endl;
    for (int i = 1; i <= 2; i++) {
        WaitForSingleObject(hEvent1, INFINITE); //wait for event to be signalled
        cout << "Inisde thread 1 and got signalled " << i << "th time" << endl;
    }
   
    CloseHandle(hOpenEvent);
    return 0;
}

DWORD WINAPI ThreadFunc4(LPVOID lpParam) {

    
    for (int i = 1; i <= 2; i++) {
        cout << "thread2 is running" << endl;
        SetEvent(hEvent1); // single the event
        Sleep(2000);
    }
    
    return 0;
}
int main31()
{
    HANDLE hThread1 = NULL, hThread2 = NULL;
    DWORD threadID1, threadID2;
    hEvent1 = CreateEvent(
        NULL,
        FALSE, //auto reset
        FALSE, //non signalled
        L"MyEvent"
    );
    if (hEvent1 == INVALID_HANDLE_VALUE) {
        cout << "Event can't be created and error number is : " << GetLastError() << endl;
        return 1;
    }
    cout << "Event succesfully created" << endl;
    hThread1 = CreateThread(
        NULL,
        0,
        ThreadFunc3,
        NULL,
        0,
        &threadID1
    );
    hThread2 = CreateThread(
        NULL,
        0,
        ThreadFunc4,
        NULL,
        0,
        &threadID2
    );
    if (hThread1 == NULL) {
        cout << "Thread 1 can't be created and error numnber is " << GetLastError() << endl;
        return 1;
    }
    cout << "Thread 1 is succesfully created " << endl;
    if (hThread2 == NULL) {
        cout << "Thread 2 can't be created and error numnber is " << GetLastError() << endl;
        CloseHandle(hThread1);
        return 1;
    }
    cout << "Thread 2 has been successfully created " << endl;
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);
    CloseHandle(hEvent1);

    system("pause");
    return 0;
}
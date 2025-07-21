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

HANDLE hEvent = NULL; //Global mutex handle

DWORD WINAPI ThreadFunc11(LPVOID lpParam) {

    WaitForSingleObject(hEvent, INFINITE); //wait for event to be signalled
    cout << "Thread1 is running" << endl;
    return 0;
}

DWORD WINAPI ThreadFunc22(LPVOID lpParam) {

    cout << "thread2 is running" << endl;
    SetEvent(hEvent); // single the event
    return 0;
}
int main30()
{
    HANDLE hThread1 = NULL, hThread2 = NULL;
    DWORD threadID1, threadID2;
    hEvent = CreateEvent(
        NULL,
        FALSE,
        FALSE,
        L"MyEvent"
    );
    if (hEvent == INVALID_HANDLE_VALUE) {
        cout << "Event can't be created and error number is : " << GetLastError() << endl;
        return 1;
    }
    cout << "Event succesfully created" << endl;
    hThread1 = CreateThread(
        NULL,
        0,
        ThreadFunc11,
        NULL,
        0,
        &threadID1
    );
    hThread2 = CreateThread(
        NULL,
        0,
        ThreadFunc22,
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
    CloseHandle(hEvent);

    system("pause");
    return 0;
}
/*
* https://learn.microsoft.com/en-us/windows/win32/sync/condition-variables
* https://learn.microsoft.com/en-us/windows/win32/sync/slim-reader-writer--srw--locks
* https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-initializeconditionvariable
void InitializeConditionVariable(
  [out] PCONDITION_VARIABLE ConditionVariable
);
//sleep in crtical section
BOOL SleepConditionVariable(
  [in, out] PCONDITION_VARIABLE ConditionVariable,
  [in, out] PCRITICAL_SECTION   CriticalSection,
  [in]      DWORD               dwMilliseconds
);
void WakeConditionVariable(
  [in, out] PCONDITION_VARIABLE ConditionVariable
);
*/

#include<windows.h>
#include <iostream>
using namespace std;

CRITICAL_SECTION cs1;
CONDITION_VARIABLE  cv;
int buffer = 0;
int max_items[20];
//output is non deterministic that is producer can create all 20 and then consumer consumes
// all 20 ietms or producer can prodcue and consumer can consume side by side
DWORD WINAPI ProducerThread(LPVOID lpParam) {
    for (int i = 0; i < 20; i++) {
        EnterCriticalSection(&cs1);
        while (buffer == 20) {
            SleepConditionVariableCS(&cv, &cs1, INFINITE);
        }
        buffer++;
        cout << "Producer produced " << buffer << " items " << endl;
        Sleep(1000);
        WakeConditionVariable(&cv);
        LeaveCriticalSection(&cs1);
    }
    return 0;
}

DWORD WINAPI ConsumerThread(LPVOID lpParam) {
    for (int i = 0; i < 20; i++) {
        EnterCriticalSection(&cs1);
        while (buffer == 0) {
            SleepConditionVariableCS(&cv, &cs1, INFINITE);
        }
        cout << "Consumer consumed " << buffer << " items " << endl;
        buffer--;
        WakeConditionVariable(&cv);
        LeaveCriticalSection(&cs1);
    }
    return 0;
}
int main32()
{
    HANDLE hProducer = NULL, hConsumer = NULL;
    InitializeCriticalSection(&cs1);
    InitializeConditionVariable(&cv);

    hProducer = CreateThread(
        NULL,
        0,
        ProducerThread,
        NULL,
        0,
        NULL
    );
    hConsumer = CreateThread(
        NULL,
        0,
        ConsumerThread,
        NULL,
        0,
        NULL
    );
    if (hProducer == NULL) {
        cout << "Prodcuer thread can't be created and error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Producer thread created succesfully " << endl;
    if (hConsumer == NULL) {
        cout << "Consumer thread can't be created and error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Consumer thread created succesfully " << endl;
    //Wake all condition variables
    WakeAllConditionVariable(&cv);

    WaitForSingleObject(hProducer, INFINITE);
    WaitForSingleObject(hConsumer, INFINITE);

    
    system("pause");
    return 0;
}
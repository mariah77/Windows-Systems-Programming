
#include<windows.h>
#include <iostream>
using namespace std;
DWORD WINAPI ThreadFunc(LPVOID lpParam) {
    cout << "Thread Running" << endl;
    return 0;
}
int main10()
{
    HANDLE hThread = NULL;
    DWORD ThreadID = 0;

    hThread = CreateThread(
        NULL,
        0,
        ThreadFunc,
        NULL,
        0,
        &ThreadID);

    if (hThread == NULL) {
        cout << "Thread creation error with error number " << GetLastError() << endl;
        return 1;
    }
    cout << "Thread creation sucessful" << endl;
    cout << "Thread ID: " << ThreadID << endl;
    CloseHandle(hThread);

    system("pause");
    return 0;
}
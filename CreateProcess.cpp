/*

A program in execution is called a process/ A process is a data structure which stores
information about process state and its memory

BOOL CreateProcessA(
  [in, optional]      LPCSTR                lpApplicationName,
  [in, out, optional] LPSTR                 lpCommandLine,
  [in, optional]      LPSECURITY_ATTRIBUTES lpProcessAttributes,
  [in, optional]      LPSECURITY_ATTRIBUTES lpThreadAttributes,
  [in]                BOOL                  bInheritHandles,
  [in]                DWORD                 dwCreationFlags,
  [in, optional]      LPVOID                lpEnvironment,
  [in, optional]      LPCSTR                lpCurrentDirectory,
  [in]                LPSTARTUPINFOA        lpStartupInfo,
  [out]               LPPROCESS_INFORMATION lpProcessInformation
);

Creates a new process and its primary thread. 
The new process runs in the security context of the calling process.

If the calling process is impersonating another user, 
the new process uses the token for the calling process, not the impersonation token.

zeromemory function initializes all the structure members to zero
*/


#include<windows.h>
#include <iostream>
using namespace std;

int main9()
{
    HANDLE hProcess = NULL;
    HANDLE hThread = NULL;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD dwProcessId = 0;
    DWORD dwThreadId = 0;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    BOOL bCreateProcess = CreateProcess(
        L"C:\\Program Files\\Windows Media Player\\wmplayer.exe",
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi);
    if (bCreateProcess == FALSE) {
        cout << "Process creation failed and error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Process sucessfully created with process ID " << pi.dwProcessId << endl;
    cout << "Thread ID is " << pi.dwThreadId << endl;
    cout << "GetProcessId function used : " << GetProcessId(pi.hProcess) << endl;
    cout << "GetThreadId function is used : " << GetThreadId(pi.hThread) << endl;
    
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    system("pause");
    return 0;
}
/*
HANDLE OpenFileMapping(
  [in] DWORD  dwDesiredAccess,
  [in] BOOL   bInheritHandle,
  [in] LPCSTR lpName
);
*/

#include<windows.h>
#include <iostream>
using namespace std;

int main22()
{
    cout << "File mapping client/child process" << endl;
    HANDLE hFileMap = NULL;
    PCHAR lpBuffer = NULL;
    
    hFileMap = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        L"LOCAL\\Mynamedfilemap"
    );
    if (hFileMap == NULL) {
        cout << "Error opening handle and error is " << GetLastError() << endl;
        return 1;
    }
    cout << "File map succesfully opened" << endl;

    lpBuffer = (PCHAR)MapViewOfFile(
        hFileMap,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        256
    );
    if (lpBuffer == NULL) {
        cout << "file can't be mapped and error number is : " << GetLastError() << endl;
        return 1;
    }
    cout << "data read from parent or server : " << lpBuffer << endl;
    if (UnmapViewOfFile(lpBuffer) == FALSE) {
        cout << "Couldn't unmap file view" << endl;
        return 1;
    }
    cout << "Succesfully unmapped file view" << endl;

     CloseHandle(hFileMap);
    

    system("pause");
    return 0;
}
/*

https://learn.microsoft.com/en-us/windows/win32/memory/file-mapping
HANDLE CreateFileMapping(
  [in]           HANDLE                hFile,
  [in, optional] LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
  [in]           DWORD                 flProtect,
  [in]           DWORD                 dwMaximumSizeHigh,
  [in]           DWORD                 dwMaximumSizeLow,
  [in, optional] LPCSTR                lpName
);
LPVOID MapViewOfFile(
  [in] HANDLE hFileMappingObject,
  [in] DWORD  dwDesiredAccess,
  [in] DWORD  dwFileOffsetHigh,
  [in] DWORD  dwFileOffsetLow,
  [in] SIZE_T dwNumberOfBytesToMap
);
void CopyMemory(
  _In_       PVOID  Destination,
  _In_ const VOID   *Source,
  _In_       SIZE_T Length
);
BOOL UnmapViewOfFile(
  [in] LPCVOID lpBaseAddress
);
*/

#include<windows.h>
#include <iostream>
using namespace std;

int main23()
{
    cout << "File mapping server/ parent process" << endl;
    HANDLE hFileMap = NULL;
    PCHAR lpBuffer = NULL;
    char buffer[1024] = "Hello I'm the server/parent and I'm using file mapping functions Win32";
    DWORD sizeBuffer = sizeof(buffer);

    hFileMap = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        256,
        L"Local\\Mynamedfilemap"
    );
    if (hFileMap == FALSE) {
        cout << "can't create file mapping and error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Succesfully created the file mapping" << endl;
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
    cout << "Sucessfully created the file mapping" << endl;
    if (lpBuffer != NULL) {
        CopyMemory(lpBuffer, buffer, sizeBuffer);
    }

    if (UnmapViewOfFile(lpBuffer) == FALSE) {
        cout << "Couldn't unmap file view" << endl;
        return 1;
    }
    cout << "Succesfully unmapped file view" << endl;
   
    system("pause");
    return 0;
}
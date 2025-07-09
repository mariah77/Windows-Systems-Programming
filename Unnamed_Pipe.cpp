/*
BOOL CreatePipe(
  [out]          PHANDLE               hReadPipe,
  [out]          PHANDLE               hWritePipe,
  [in, optional] LPSECURITY_ATTRIBUTES lpPipeAttributes,
  [in]           DWORD                 nSize
);
*/

#include<windows.h>
#include <iostream>
using namespace std;

int main17()
{
    BOOL bFile;
    char chBuffer[512] = "Pipe read and write operation";
    DWORD dwNoOfBytesToWrite = strlen(chBuffer);
    DWORD dwNoOfBytesWritten = 0;
    DWORD dwNoOfBytesToRead = strlen(chBuffer);
    DWORD dwNoOfBytesRead = 0;
    HANDLE hWrite = NULL, hRead = NULL;
    

    BOOL bCreatePipe = CreatePipe(
        &hRead,
        &hWrite,
        NULL,
        dwNoOfBytesToWrite
    );
    //write to pipe
    bFile = WriteFile(hWrite,
        chBuffer,
        dwNoOfBytesToWrite,
        &dwNoOfBytesWritten,
        NULL);
    if (hWrite == INVALID_HANDLE_VALUE) {
        cout << "Writing to pipe failed and Error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Write operation successful" << endl;
    CloseHandle(hWrite);
    
    //Read from Pipe
    bFile = ReadFile(hRead,
        chBuffer,
        dwNoOfBytesToRead,
        &dwNoOfBytesRead,
        NULL);
    if (bFile == FALSE) {
        cout << "Reading from pipe operation failed " << GetLastError() << endl;
        return 1;
    }
    cout << "Read from pipe succesfully" << endl;
    CloseHandle(hRead);
    system("pause");
    return 0;
}
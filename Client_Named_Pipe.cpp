/*
HANDLE CreateNamedPipe(
  [in]           LPCSTR                lpName,
  [in]           DWORD                 dwOpenMode,
  [in]           DWORD                 dwPipeMode,
  [in]           DWORD                 nMaxInstances,
  [in]           DWORD                 nOutBufferSize,
  [in]           DWORD                 nInBufferSize,
  [in]           DWORD                 nDefaultTimeOut,
  [in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
BOOL ConnectNamedPipe(
  [in]                HANDLE       hNamedPipe,
  [in, out, optional] LPOVERLAPPED lpOverlapped
);
BOOL FlushFileBuffers(
  [in] HANDLE hFile
);
BOOL DisconnectNamedPipe(
  [in] HANDLE hNamedPipe
);
*/

#include<windows.h>
#include <iostream>
using namespace std;

int main19()
{
    BOOL bFile;
    HANDLE hFile = NULL;
    char inputBuffer[1023];
    char outputBuffer[1023];
    DWORD dwSizeOutputBuffer = sizeof(outputBuffer);
    DWORD dwSizeInputBuffer = sizeof(inputBuffer);
    char readBuffer[512];
    char writeBuffer[512] = "Pipe write operation";
    DWORD sizeReadBuffer = sizeof(readBuffer);
    DWORD sizeWriteBuffer = sizeof(writeBuffer);

    DWORD dwNoOfBytesWrite = 0;
    DWORD dwNoOfBytesRead = 0;

    cout << "This is the named pipe client" << endl;
    hFile = CreateFile( //create named pipe function can't open an existing pipe hence need createfile function to open an existing pipe
        L"\\\\.\\pipe\\MyNamedPipe",/* Syntax for writing pipe name is \\.\pipe\your_pipe_name  */
        GENERIC_READ|GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (hFile == INVALID_HANDLE_VALUE) {
        cout << "File creation error with error number" << GetLastError() << endl;
        return 1;
    }
    cout << "File creation succesful" << endl;
 
    //Read from Pipe
    bFile = ReadFile(
        hFile,
        readBuffer,
        sizeReadBuffer,
        &dwNoOfBytesRead,
        NULL);
    if (bFile == FALSE) {
        cout << "Reading from file operation failed " << GetLastError() << endl;
        return 1;
    }
    cout << "Read file succesful" << endl;
    cout << "Data read from server: " << readBuffer << endl;
    
    //write to pipe
    bFile = WriteFile(
        hFile,
        writeBuffer,
        sizeWriteBuffer,
        &dwNoOfBytesWrite,
        NULL);
    if (bFile == FALSE) {
        cout << "Writing to file failed and Error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Write operation successful" << endl;
    CloseHandle(hFile);
    system("pause");
    return 0;
}
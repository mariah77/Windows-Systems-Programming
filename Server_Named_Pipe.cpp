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
https://learn.microsoft.com/en-us/windows/win32/ipc/named-pipe-operations
*/

#include<windows.h>
#include <iostream>
using namespace std;

int main()
{
    BOOL bFile;
    HANDLE hCreateNamedPipe = NULL;
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

    cout << "This is the named server" << endl;
    hCreateNamedPipe = CreateNamedPipe(
        L"\\\\.\\pipe\\MyNamedPipe",/* Syntax for writing pipe name is \\.\pipe\your_pipe_name  */
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        dwSizeOutputBuffer,
        dwSizeInputBuffer,
        0,
        NULL
    );
    if (hCreateNamedPipe == INVALID_HANDLE_VALUE) {
        cout << "Named pipe creation failed with error number" <<GetLastError()<< endl;
        return 1;
    }
    cout << "Named pipe creation succesful" << endl;
    if (ConnectNamedPipe(hCreateNamedPipe, NULL) == FALSE) {
        cout << "Named pipe can't be connected with error number: " << GetLastError() << endl;
        return 1;
    }
    cout << "Named pipe succesfully conncted" << endl;
    //write to pipe
    bFile = WriteFile(
        hCreateNamedPipe,
        writeBuffer,
        sizeWriteBuffer,
        &dwNoOfBytesWrite,
        NULL);
    if (bFile == FALSE) {
        cout << "Writing to pipe failed and Error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Write operation successful" << endl;

    //flush the file buffer
    if (FlushFileBuffers(hCreateNamedPipe) == FALSE) {
        cout << "Buffer could not be flushed with error " << GetLastError() << endl;
        return 1;
    }
    cout << "Buffer flushed succesfully" << endl;
    //Read from Pipe
    bFile = ReadFile(
        hCreateNamedPipe,
        readBuffer,
        sizeReadBuffer,
        &dwNoOfBytesRead,
        NULL);
    if (bFile == FALSE) {
        cout << "Reading from pipe operation failed " << GetLastError() << endl;
        return 1;
    }
    cout << "Read from pipe succesfully" << endl;
    cout << "Data read from client: " << readBuffer << endl;
    //Now discinnect the named pipe
    if (DisconnectNamedPipe(hCreateNamedPipe) == FALSE) {
        cout << "Named pipe couldn't be disconncted and error is " << GetLastError() << endl;
    }
    cout << "Pipe succesfully disconnected " << endl;
    CloseHandle(hCreateNamedPipe);
    system("pause");
    return 0;
}
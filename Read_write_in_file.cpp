//void pointer can point to any datatype

#include<windows.h>
#include <iostream>
using namespace std;

int main5()
{
    BOOL bFile;
    char chBuffer[] = "Read and Write from File using Win32 API";
    DWORD dwNoOfBytesToWrite = strlen(chBuffer);
    DWORD dwNoOfBytesWritten = 0;
    DWORD dwNoOfBytesToRead = strlen(chBuffer);
    DWORD dwNoOfBytesRead = 0;
    HANDLE hFile = CreateFile(L"Your File Path",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        cout << "CreateFile failed and Error number is " << GetLastError() << endl;
    }
    cout << "File created succesfully" << endl;
    //WriteFile
    bFile = WriteFile(hFile,
        chBuffer,
        dwNoOfBytesToWrite,
        &dwNoOfBytesWritten,
        NULL);
    if (bFile == FALSE) {
        cout << "WriteFile operation failed " << GetLastError() << endl;
    }
    cout << "Write operation successful" << endl;

    //ReadFile 
    bFile = ReadFile(hFile,
        chBuffer,
        dwNoOfBytesToRead,
        &dwNoOfBytesRead,
        NULL);
    if (bFile == FALSE) {
        cout << "File read operation failed " << GetLastError() << endl;
    }
    cout << "File read operation successful" << endl;
    cout << "Data read : " << chBuffer << endl;
    CloseHandle(hFile);

    system("pause");
    return 0;
}
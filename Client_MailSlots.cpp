/*
same code as of creating and writing to a file
);
*/

#include<windows.h>
#include <iostream>
#include<string>
using namespace std;

int main20()
{
    cout << "Mail slot client " << endl;
    HANDLE hCreateFile = NULL, hSlots = NULL;
    char writeBuffer[1023] = "This is the sample message to be written in mailslot program";
    DWORD writeBufferSize = sizeof(writeBuffer);
    DWORD noOfBytesWrite;
   

    //create mailslots
    hCreateFile = CreateFile(
        L"\\\\.\\mailslot\\MyMailsLot",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (hCreateFile == INVALID_HANDLE_VALUE) {
        cout << "error opening mailslot and error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Mailslot opened succesfully" << endl;
    
    if (WriteFile(hCreateFile, writeBuffer, writeBufferSize, &noOfBytesWrite, NULL) == NULL) {

        cout << "Error writing to server and error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Succesfully wrote to server" <<  endl;
    CloseHandle(hCreateFile);
    system("pause");
    return 0;
}
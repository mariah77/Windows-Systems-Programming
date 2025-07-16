/*
one way inter process communication
can be used both locally and over a network --> advantage over anonymous pipe
client-server
messages sent via datagrams 
there is no mechanism to confirm if the message has been received
https://learn.microsoft.com/en-us/windows/win32/ipc/mailslots
HANDLE CreateMailslotA(
  [in]           LPCSTR                lpName,
  [in]           DWORD                 nMaxMessageSize,
  [in]           DWORD                 lReadTimeout,
  [in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
*/

#include<windows.h>
#include <iostream>
using namespace std;

int main21()
{
    cout << "Mail slot server " << endl;
    HANDLE hSlots= NULL;
    char readBuffer[1023];
    DWORD bufferSize = sizeof(readBuffer);
    DWORD noOfBytesRead;

    //create mailslots
    hSlots = CreateMailslot(
        L"\\\\.\\mailslot\\MyMailsLot",
        0,
        MAILSLOT_WAIT_FOREVER,
        NULL
    );
    if (hSlots == INVALID_HANDLE_VALUE) {
        cout << "error creating mailslots and error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Mailslot created succesfully" << endl;
    if(ReadFile(hSlots, readBuffer, bufferSize, &noOfBytesRead, NULL) == NULL){
    
        cout << "Error reading from client and error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Succesfully read from client, message is: " << readBuffer << endl;
    CloseHandle(hSlots);
    system("pause");
    return 0;
}
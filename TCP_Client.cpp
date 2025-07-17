/*
* int WSAAPI listen(
  [in] SOCKET s,
  [in] int    backlog
);

SOCKET WSAAPI accept(
  [in]      SOCKET   s,
  [out]     sockaddr *addr,
  [in, out] int      *addrlen
);

int WSAAPI send(
  [in] SOCKET     s,
  [in] const char *buf,
  [in] int        len,
  [in] int        flags
);

int recv(
  [in]  SOCKET s,
  [out] char   *buf,
  [in]  int    len,
  [in]  int    flags
);

int WSAAPI connect(
  [in] SOCKET         s,
  [in] const sockaddr *name,
  [in] int            namelen
);
*/

//------------------------------VERY IMPORTANT CONFIGUARTION for Visual Studios------------------------------
//Right click on project -> properties 
//go to linker under general configuration
//linker -> input
//Add WS2_32.lib under additional dependencies 
//Select OK-> APPLY 
// **Ws2_32.dll** is the actual DLL (Dynamic-Link Library) 
// that contains the runtime implementations of all Winsock 2 functions
//-----------------------------------------------------------------------------------------------------

#include<windows.h>
#include <iostream>
using namespace std;

int main27()
{
    cout << "TCP Client" << endl;
    //create following three to initalize the DLL
    WSADATA WinSockData;
    int iWSAStartup;
    int iWSACleanup;

    SOCKET TCPSocketClient;
    SOCKET sAcceptSocket;
    struct sockaddr_in TCPServerAddress;
    int TCPServerLen = sizeof(TCPServerAddress);

    char sendBuffer[512] = "Hello from client";
    char receiveBuffer[512];
    int sizeBufferSend = strlen(sendBuffer) + 1;
    int sizeBufferReceive = strlen(receiveBuffer) + 1;
    int iConnect;
    int iSend;
    int iRec;
  

    //initialize winsock
    iWSAStartup = WSAStartup(MAKEWORD(2, 2), &WinSockData);
    if (iWSAStartup != 0) {
        cout << "WSAStartup failed and error number is " << WSAGetLastError() << endl;
        return 1;
    }

    cout << "WSAStartup succeeded" << endl;
    // Fill the TCPServerAdress structures
    TCPServerAddress.sin_family = AF_INET; //The values currently supported are AF_INET or AF_INET6, which are the Internet address family formats for IPv4 and IPv6. 
    TCPServerAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    TCPServerAddress.sin_port = htons(8000); //converts little endian to big endian, everything like laptops etc run in big endian format

    //socket creation
    TCPSocketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (TCPSocketClient == INVALID_SOCKET) {
        cout << "Error creating TCP client socket and error number is " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Successfully created the socket " << endl;

    //bind the server
    
    
    iConnect = connect(
        TCPSocketClient,
        (SOCKADDR*)&TCPServerAddress,
        TCPServerLen

    );
    if (iConnect == SOCKET_ERROR) {
        cout << "Connection failed and error number is " << WSAGetLastError() << endl;
        return 1;
    }

    cout << "Connection succesfully established" << endl;
  
    //receive data from server
    iRec = recv(
        TCPSocketClient,
        receiveBuffer,
        sizeBufferReceive,
        0
    );
    if (iRec == SOCKET_ERROR) {
        cout << "Couldn't receive data from server and the error number is " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Received data from server: " << receiveBuffer << endl;
    //send data to server

    iSend = send(
        TCPSocketClient,
        sendBuffer,
        sizeBufferSend,
        0
    );
    if (iSend == SOCKET_ERROR) {
        cout << "Client couldn't send data to server and the error number is " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Client sent : " << sendBuffer << endl;

    
   
    //close socket 
    if (closesocket(TCPSocketClient) == SOCKET_ERROR) {
        cout << "error closing socket and error number is : " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Socket has been closed " << endl;
    //WSAClenup up for terminating the DLL 
    iWSACleanup = WSACleanup();

    if (iWSACleanup == SOCKET_ERROR) {
        cout << "WSA cleanup failed and error is " << WSAGetLastError() << endl;
    }
    cout << "Cleanup at clinet side succesfull" << endl;
    system("pause");
    return 0;
}
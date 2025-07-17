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

int main()
{
    cout << "TCP server" << endl;
    //create following three to initalize the DLL
    WSADATA WinSockData;
    int iWSAStartup;
    int iWSACleanup;

    SOCKET TCPSocketServer;
    SOCKET sAcceptSocket;
    struct sockaddr_in TCPClientAddress;
    struct sockaddr_in TCPServerAddress;

    char sendBuffer[512] = "Hello from server";
    char receiveBuffer[512] = "Hello from server";
    int sizeBufferSend = strlen(sendBuffer) + 1;
    int sizeBufferReceive = strlen(receiveBuffer) + 1;

    int  ibind;
    int iListen;
    int iSend;
    int iRec;
    int TCPClientLen = sizeof(TCPClientAddress);
    int CloseSocket;

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
    TCPSocketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (TCPSocketServer == INVALID_SOCKET) {
        cout << "Error creating TCP server socket and error number is " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Successfully created the socket " << endl;

    //bind the server
    ibind = bind(
        TCPSocketServer,
        (SOCKADDR*)&TCPServerAddress,
        sizeof(TCPServerAddress)
    );
    if (ibind == SOCKET_ERROR) {
        cout << "error in binding the socket and error number is " << WSAGetLastError << endl;
        return 1;
    }
    cout << "Binding with socket succesful" << endl;
    //receive data from client
    iListen = listen(
       TCPSocketServer,
        2
    );
    if (iListen == SOCKET_ERROR) {
        cout << "listen function failed and error number is " << WSAGetLastError() << endl;
        return 1;
    }

    cout << "Server is listening" << endl;
    sAcceptSocket = accept(
        TCPSocketServer,
        (SOCKADDR*)&TCPClientAddress,
        &TCPClientLen
    );
    if (sAcceptSocket == INVALID_SOCKET) {
        cout << "connected not accepted and error number is " << WSAGetLastError() << endl;
        return 1;
     }
    cout << "Connection accepted " << endl;

    //send data to client
    
    iSend = send(
        sAcceptSocket,
        sendBuffer,
        sizeBufferSend,
        0
    );
    if (iSend == SOCKET_ERROR) {
        cout << "Server couldn't send data to client and the error number is " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Server sent : " << sendBuffer << endl;

    //receive data from client
    iRec = recv(
        sAcceptSocket,
        receiveBuffer,
        sizeBufferReceive,
        0
    );
    if (iRec == SOCKET_ERROR) {
        cout << "Couldn't receive data from client and the error number is " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Received data from client: " << receiveBuffer << endl;
    //close socket 
    if (closesocket(TCPSocketServer) == SOCKET_ERROR) {
        cout << "error closing socket and error number is : " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Socket has been closed " << endl;
    //WSAClenup up for terminating the DLL 
    iWSACleanup = WSACleanup();

    if (iWSACleanup == SOCKET_ERROR) {
        cout << "WSA cleanup failed and error is " << WSAGetLastError() << endl;
    }
    cout << "Cleanup at server side successful" << endl;
    system("pause");
    return 0;
}
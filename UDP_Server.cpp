/*
int WSAStartup(
  [in]  WORD      wVersionRequired,
  [out] LPWSADATA lpWSAData
);
typedef struct sockaddr_in {
  short          sin_family;
  u_short        sin_port;
  struct in_addr sin_addr;
  char           sin_zero[8];
} SOCKADDR_IN, *PSOCKADDR_IN, *LPSOCKADDR_IN;

SOCKET WSAAPI socket(
  [in] int af,
  [in] int type,
  [in] int protocol
);
u_short htons(
  [in] u_short hostshort
);
int bind(
  [in] SOCKET         s,
       const sockaddr *addr,
  [in] int            namelen
);
int recvfrom(
  [in]                SOCKET   s,
  [out]               char     *buf,
  [in]                int      len,
  [in]                int      flags,
  [out]               sockaddr *from,
  [in, out, optional] int      *fromlen
);
int closesocket(
  [in] SOCKET s
);
int WSACleanup();

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

int main24()
{
    cout << "UDP server" << endl;
    WSADATA WinSockData;
    int iWSAStartup;
    int iWSACleanup;

    SOCKET UDPSocketServer;
    struct sockaddr_in UDPClient;

    char buffer[512];
    int sizeBuffer = strlen(buffer) + 1;

    int  ibind;
    int receivedFrom;
    int UDPClientLen = sizeof(UDPClient);
    int CloseSocket;

    //initialize winsock
    iWSAStartup = WSAStartup(MAKEWORD(2, 2), &WinSockData);
    if (iWSAStartup!=0) {
        cout << "WSAStartup failed and error number is " << WSAGetLastError() << endl;
        return 1;
    }

    cout << "WSAStartup succeeded" << endl;
    // Fill the UDPClient(Socket address) structure
    UDPClient.sin_family = AF_INET; //The values currently supported are AF_INET or AF_INET6, which are the Internet address family formats for IPv4 and IPv6. 
    UDPClient.sin_addr.s_addr = inet_addr("127.0.0.1");
    UDPClient.sin_port = htons(8001); //converts little endian to big endian, everything like laptops etc run in big endian format

    //socket creation
    UDPSocketServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (UDPSocketServer == INVALID_SOCKET) {
        cout << "Error creating socket and error number is " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Successfully created the socket " << endl;
    
    //bind the server
    ibind = bind(
        UDPSocketServer,
        (SOCKADDR*)&UDPClient,
        sizeof(UDPClient)
    );
    if (ibind == SOCKET_ERROR) {
        cout << "error in binding the socket and error number is " << WSAGetLastError << endl;
        return 1;
    }

    //receive data from client
    receivedFrom = recvfrom(
        UDPSocketServer,
        buffer,
        sizeBuffer,
        MSG_PEEK,
        (SOCKADDR*)&UDPClient,
        &UDPClientLen
    );
    if (receivedFrom == SOCKET_ERROR) {
        cout << "Data cannot be received from client and error number is " << WSAGetLastError() << endl;
        return 1;
    }

    cout << "Data succesfully received from client" << endl;
    cout << "Data received from client is: " << buffer << endl;
    //close socket 
    if (closesocket(UDPSocketServer) == SOCKET_ERROR) {
        cout << "error closing socket and error number is : " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Socket has been closed " << endl;
    //WSAClenup up for terminating the DLL 
    iWSACleanup = WSACleanup();

    if (iWSACleanup == SOCKET_ERROR) {
       cout << "WSA cleanup failed and error is " << WSAGetLastError() << endl;
    }
    system("pause");
    return 0;
}
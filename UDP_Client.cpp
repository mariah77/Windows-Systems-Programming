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
int sendto(
  [in] SOCKET         s,
  [in] const char     *buf,
  [in] int            len,
  [in] int            flags,
  [in] const sockaddr *to,
  [in] int            tolen
);
MSG_DONTROUTE 	Specifies that the data should not be subject to routing.
A Windows Sockets service provider can choose to ignore this flag.
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
//-----------------------------------------------------------------------------------------------------

#include<windows.h>
#include <iostream>
using namespace std;

int main26()
{
    cout << "UDP client" << endl;
    WSADATA WinSockData;
    int iWSAStartup;
    int iWSACleanup;

    SOCKET UDPSocketClient;
    struct sockaddr_in UDPServer;

    char buffer[512] = "Hello from UDP Client";
    int sizeBuffer = strlen(buffer) + 1;
    int iSendto;


    int  ibind;
    int UDPServerLen = sizeof(UDPServer);
    int CloseSocket;

    //initialize winsock
    iWSAStartup = WSAStartup(MAKEWORD(2, 2), &WinSockData);
    if (iWSAStartup != 0) {
        cout << "WSAStartup failed and error number is " << WSAGetLastError() << endl;
        return 1;
    }

    cout << "WSAStartup succeeded" << endl;
    // Fill the UDPServer(Socket address) structure
    UDPServer.sin_family = AF_INET; //The values currently supported are AF_INET or AF_INET6, which are the Internet address family formats for IPv4 and IPv6. 
    UDPServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    UDPServer.sin_port = htons(8001); //converts little endian to big endian, everything like laptops etc run in big endian format

    //socket creation
    UDPSocketClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (UDPSocketClient == INVALID_SOCKET) {
        cout << "Error creating socket and error number is " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Successfully created the socket " << endl;

    //bind the server
    /*ibind = bind(
        UDPSocketServer,
        (SOCKADDR*)&UDPClient,
        sizeof(UDPClient)
    );
    if (ibind == SOCKET_ERROR) {
        cout << "error in binding the socket and error number is " << WSAGetLastError << endl;
        return 1;
    }*/

    //receive data from client
    iSendto = sendto(
        UDPSocketClient,
        buffer,
        sizeBuffer,
        MSG_DONTROUTE,
        (SOCKADDR*)&UDPServer,
        sizeof(UDPServer)
    );
    if (iSendto == SOCKET_ERROR) {
        cout << "Data cannot be sent to server and error number is " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Data succesfully sent to server" << endl;
    //close socket 
    if (closesocket(UDPSocketClient) == SOCKET_ERROR) {
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
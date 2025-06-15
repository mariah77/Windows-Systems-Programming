
#include<windows.h>
#include <iostream>
#include<string>
using namespace std;

int main4()
{
    HANDLE hFile = CreateFile(L"Your file path",
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
    CloseHandle(hFile);

    system("pause");
    return 0;
}



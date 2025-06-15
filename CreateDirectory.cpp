
#include<windows.h>
#include <iostream>
#include<string>
using namespace std;

int main1()
{
    LPCTSTR path = L"Your Directory path";
    BOOL success = false;
    
    success = CreateDirectory(path,
                NULL);

    if (success == 0) {
        cout << "CreateDirectory Function Failed and Error Number: " << GetLastError() << endl;
    }
    else {
        cout << "Directory successfully created" << endl;
    }
    if (RemoveDirectory(path)) {
        cout << "Directory succesfully removed " << endl;
    }
    else {
        cout << "Failed to remove directory and Error Number : " << GetLastError() << endl;
    }
    system("pause");
    return 0;
}



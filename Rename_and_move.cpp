
#include<windows.h>
#include <iostream>
#include<string>
using namespace std;

int main3()
{
    LPCTSTR oldFileName = L"Your old file path";
    LPCTSTR newFileName = L"Your new file path";
    LPCTSTR oldDirectory = L"Your old directory path";
    LPCTSTR newDirectory = L"Your new directory path";
    if (MoveFile(oldFileName, newFileName)) {
        cout << "File moved sucessfully" << endl;
    }
    else {
        cout << "File move error, Error Number: " << GetLastError() << endl;
    }
    
    if (MoveFile(oldDirectory, newDirectory)) {
        cout << "Directory moved sucessfully" << endl;
    }
    else {
        cout << "Directory move error, Error Number: " << GetLastError() << endl;
    }

    system("pause");
    return 0;
}



#include<windows.h>
#include <iostream>
#include<string>
using namespace std;

int main2()
{
    LPCTSTR fileToCopy = L"Your file path";
    LPCTSTR copiedFile = L"Your new file path";
    BOOL bFailExists = FALSE; // No error occurs if teh new file to be created already exists

    if (CopyFile(fileToCopy, copiedFile, bFailExists)) {
        cout << "File successfully copied" << endl;
    }
    else {
        cout << " File copy Error, Error Number :  " << GetLastError() << endl;
    }
    system("pause");
    return 0;
}



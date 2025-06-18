/*

BOOLEAN CreateSymbolicLink(
  [in] LPCSTR lpSymlinkFileName,
  [in] LPCSTR lpTargetFileName,
  [in] DWORD  dwFlags
);

Run this file under administrative access other wise will get Error number: 1314 
File or directory created will take 0 KB because no space is taken up on physical memory
Symlink is a shortcut for an original file/folder

*/


#include<windows.h>
#include <iostream>
using namespace std;

int main7()
{
    LPCTSTR filePath = L"Your file path";
    LPCTSTR directoryPath = L"Your directory path";
    LPCTSTR softLinkFilePath = L"Your soft link file path";
    LPCTSTR softLinkDirectoryPath = L"Your soft link directory path";
    if (CreateSymbolicLink(softLinkFilePath, filePath, 0) == 0) {
        cout << "Error creating symbolic link and error number is " << GetLastError() << endl;
        
    }
    if (CreateSymbolicLink(softLinkDirectoryPath, directoryPath, SYMBOLIC_LINK_FLAG_DIRECTORY) == 0) {
        cout << "Error creating symbolic link directory and error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Symbolic link for file and directory successfully created" << endl;
    system("pause");
    return 0;
}
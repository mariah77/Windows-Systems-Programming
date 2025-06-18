/*

BOOL CreateHardLink(
  [in] LPCSTR                lpFileName,
  [in] LPCSTR                lpExistingFileName,
       LPSECURITY_ATTRIBUTES lpSecurityAttributes
);

Establishes a hard link between an existing file and a new file.
This function is only supported on the NTFS file system,and only for files,
not directories.
If you change the contents of the hardlink then the original file contents will
also be changed

security attributes NULL means that the secuirty attribute goes to current
object and that none of teh child processes can inherit the handle

*/


#include<windows.h>
#include <iostream>
using namespace std;

int main6()
{
    LPCTSTR hardLinkPath = L"Your file path";
    LPCTSTR filePath = L"Your file path";
    if (CreateHardLink(hardLinkPath, filePath, NULL)) {
        cout << "Hard link successfully created " << endl;
    }
    else {
        cout << "Hard link creation error and Error number is " << GetLastError() << endl;
    }

    system("pause");
    return 0;
}
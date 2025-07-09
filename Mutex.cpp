

#include<windows.h>
#include <iostream>
using namespace std;

int main13()
{
    HANDLE unnamedMutex = NULL;
    HANDLE namedMutex = NULL;
    unnamedMutex = CreateMutex(NULL, FALSE, NULL);
    namedMutex = CreateMutex(NULL, FALSE, L"MyMutex");
    if (unnamedMutex == NULL) {
        cout << "Mutex creation error with error number : " << GetLastError() << endl;
        return 1;
    }
    cout << "Unnamed Mutex succesfully created" << endl;

    if (namedMutex==NULL) {
        cout << "Mutex creation error with error number : " << GetLastError() << endl;
        return 1;
    }
    cout << "Named Mutex succesfully created" << endl;
    getchar();
    CloseHandle(unnamedMutex);
    CloseHandle(namedMutex);
    system("pause");
    return 0;
}
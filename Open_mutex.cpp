/*
Comment out line 24, from Mutex.cpp file
namedMutex handle should not be closed so that open mutex can find and open it 
*/


#include<windows.h>
#include <iostream>
using namespace std;

int main12(){
    HANDLE namedMutex = NULL;
   
    cout << "Mutex Open Function" << endl;
    namedMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"MyMutex");
    if (namedMutex == NULL) {
        cout << "Mutex OPEN error with error number : " << GetLastError() << endl;
        return 1;
    }
    cout << "Named Mutex succesfully opened" << endl;

    CloseHandle(namedMutex);
    system("pause");
    return 0;
}
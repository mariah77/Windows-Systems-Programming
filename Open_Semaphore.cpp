//comment out line 48 in Semaphore.cpp. Named sempahore semaphore's handle cannot be closed for it to be opened by another program.
// create two different projects 
//In one run Semapphore.cpp and in the other run Open_Sempahore and see the output



#include<windows.h>
#include <iostream>
using namespace std;


int main15()
{
    HANDLE namedSemaphore = NULL;
    namedSemaphore = OpenSemaphore(
        SEMAPHORE_ALL_ACCESS,
        FALSE,
        L"MySemaphore"
    );

    if (namedSemaphore == NULL ) {
        cout << "Semaphore can't be opned. Error number is  " << GetLastError() << endl;
        return 1;
    }
    cout << "Semaphore opened succesfully" << endl;

    getchar();

    CloseHandle(namedSemaphore);
    
    system("pause");
    return 0;
}
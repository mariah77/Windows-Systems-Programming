#include<windows.h>
#include <iostream>
using namespace std;

int a[2];
DWORD Sum(LPVOID lpParam) {

    cout << "Sum: " << a[0] + a[1] << endl;
    return 0;
}
int main11()
{
    DWORD ThreadID = 0;
    HANDLE hThread = NULL;
    cout << "Enter your 1st Number: ";
    cin >> a[0];
    cout << "Enter your 2nd Number: ";
    cin >> a[1];
    if (CreateThread(NULL, 0, Sum, (void*)&a, 0, &ThreadID) == NULL) {
        cout << "Thread creation error with error numnber" << GetLastError() << endl;
        return 1;
    }
    
    system("pause");
    return 0;
}
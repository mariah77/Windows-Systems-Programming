/*
* LONG InterlockedAdd64(
  [in, out] LONG volatile *Addend,
  [in]      LONG          Value
);
LONG InterlockedIncrement(
  [in, out] LONG volatile *Addend
);

*/

#include<windows.h>
#include <iostream>
using namespace std;
int main()
{
    volatile LONG64 a = 5;
    volatile LONG64 b;
    b = InterlockedAdd64(&a, 5);
    cout << "Addition : " << b << endl;

    volatile LONG64 x = 7;
    volatile LONG64 y;
    y = InterlockedIncrement64(&x);
    cout << "Incremented x : " << y << endl;
    system("pause");
    return 0;
}
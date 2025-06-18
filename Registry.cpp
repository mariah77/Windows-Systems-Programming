/*



LSTATUS RegCreateKeyEx(
  [in]            HKEY                        hKey,
  [in]            LPCSTR                      lpSubKey,
                  DWORD                       Reserved,
  [in, optional]  LPSTR                       lpClass,
  [in]            DWORD                       dwOptions,
  [in]            REGSAM                      samDesired,
  [in, optional]  const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  [out]           PHKEY                       phkResult,
  [out, optional] LPDWORD                     lpdwDisposition
);

Creates the specified registry key.
If the key already exists, the function opens it.
Note that key names are not case sensitive.

LSTATUS RegSetValueEx(
  [in]           HKEY       hKey,
  [in, optional] LPCSTR     lpValueName,
                 DWORD      Reserved,
  [in]           DWORD      dwType,
  [in]           const BYTE *lpData,
  [in]           DWORD      cbData
);
*/


#include<windows.h>
#include <iostream>
using namespace std;

int main8()
{
    LSTATUS lReg;
    HKEY hKey;
    DWORD dwData = 1234;
    lReg = RegCreateKeyEx(
        HKEY_LOCAL_MACHINE,
        L"Software\\Test\\Product\\SmartId",
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS | KEY_WOW64_64KEY,
        NULL,
        &hKey,
        NULL);

    if (lReg != ERROR_SUCCESS) {
        cout << "Registry cannot be created and error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Registry successfully created" << endl;

    //set the newly created registry's value

    if (RegSetValueEx(hKey, L"VALUE", NULL, REG_DWORD, (LPBYTE)&dwData, sizeof(dwData)) != ERROR_SUCCESS) {
        cout << "Registry key value could not be set and error number is " << GetLastError() << endl;
        return 1;
    }
    cout << "Registry value succesfully set" <<endl;
    RegCloseKey(hKey);
    system("pause");
    return 0;
}
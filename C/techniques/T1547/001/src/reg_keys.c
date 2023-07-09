/*
 * This program set itself into Windows startup by using Registry Keys Run or RunOnce within HKCU
 * It checks if it was already set before.
 * It's also possible to set the same subkeys on HKLM, but it requires ADMIN privileges.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


int main() {
    LPCWSTR subkeyName = L"progName";
    WCHAR progPath[MAX_PATH];
    GetModuleFileNameW(NULL, progPath, MAX_PATH);

    HKEY hSetRunKey, hReadRunKey;
    
    // You can choose any of the keys below to use in the next functions
    LPCWSTR runKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    LPCWSTR runOnceKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce";

    WCHAR existingValue[MAX_PATH + 1];
    DWORD existingValueSize = sizeof(existingValue);

    // If you replace HKCU with HKLM, the program will need to be executed as ADMIN
    if (RegOpenKeyExW(HKEY_CURRENT_USER, runKey, 0, KEY_QUERY_VALUE, &hReadRunKey) == ERROR_SUCCESS) {
        if (RegGetValueW(hReadRunKey, NULL, subkeyName, RRF_RT_REG_SZ, NULL, existingValue, &existingValueSize) == ERROR_SUCCESS) {
            int status = wcscmp(existingValue, progPath);
            if (status == 0) {
                printf("%ls already added into registry.\n", existingValue);
            }
        } else {
            if (RegOpenKeyExW(HKEY_CURRENT_USER, runKey, 0, KEY_SET_VALUE, &hSetRunKey) == ERROR_SUCCESS) {
                if (RegSetValueExW(hSetRunKey, subkeyName, 0, REG_SZ, (const BYTE*)progPath, sizeof(progPath)) != ERROR_SUCCESS) {
                    printf("Failed to add program to startup registry.\n");
                }

                RegCloseKey(hSetRunKey);
            }
        }

        RegCloseKey(hReadRunKey);
    }

    system("pause");

    return EXIT_SUCCESS;
}

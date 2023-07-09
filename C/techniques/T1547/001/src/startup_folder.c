/*
 * This program copies itself to startup folder (%appdata%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\newname.exe)
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


int main() {
    char currentPath[MAX_PATH];
    char destPath[MAX_PATH];
    char* userProfilePath = getenv("appdata");

    // DWORD GetModuleFileNameW(
    //     [in, optional] HMODULE hModule,
    //     [out]          LPWSTR  lpFilename,
    //     [in]           DWORD   nSize
    // );

    if (!GetModuleFileName(NULL, currentPath, MAX_PATH)) {
        printf("Error while getting Module Name: %d\n", GetLastError());
    } else {
        printf("Path = %s\n", currentPath);
    }

    // BOOL CopyFile(
    //     [in] LPCTSTR lpExistingFileName,
    //     [in] LPCTSTR lpNewFileName,
    //     [in] BOOL    bFailIfExists
    // );

    snprintf(destPath, sizeof(destPath), "%s\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\newname.exe", userProfilePath);

    // It will fail if it can't be copied so we can see the error code.
    if (!CopyFile(currentPath, destPath, TRUE)) {
        printf("Error while copying file. GetLastError = %d", GetLastError());
    }

    // Works only if executed as ADMIN. If fails, returns error 0x5 (Access denied)
    if (!CopyFile(currentPath, "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\StartUp\\newname.exe", TRUE)) {
        printf("Error while copying file. GetLastError = %d", GetLastError());
    }

    system("pause");

    return EXIT_SUCCESS;
}

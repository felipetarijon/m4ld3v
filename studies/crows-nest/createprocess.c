#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


int main(void) {
    // BOOL CreateProcessW(
    //     [in, optional]      LPCWSTR               lpApplicationName,
    //     [in, out, optional] LPWSTR                lpCommandLine,
    //     [in, optional]      LPSECURITY_ATTRIBUTES lpProcessAttributes,
    //     [in, optional]      LPSECURITY_ATTRIBUTES lpThreadAttributes,
    //     [in]                BOOL                  bInheritHandles,
    //     [in]                DWORD                 dwCreationFlags,
    //     [in, optional]      LPVOID                lpEnvironment,
    //     [in, optional]      LPCWSTR               lpCurrentDirectory,
    //     [in]                LPSTARTUPINFOW        lpStartupInfo,
    //     [out]               LPPROCESS_INFORMATION lpProcessInformation
    // );

    STARTUPINFOW si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    
    if (!CreateProcessW(
        L"C:\\Windows\\System32\\calc.exe",
        NULL,
        NULL,
        NULL,
        FALSE,
        NORMAL_PRIORITY_CLASS,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        printf("(-) Error while creating process: %ld\n", GetLastError());
        EXIT_FAILURE;
    }

    printf("(+) Process created successfully. PID = %ld\n", pi.dwProcessId);
    printf("\t(+) PID = %ld, handle: %x\n", pi.dwProcessId, pi.hProcess);
    printf("\t(+) TID = %ld, handle: %x\n", pi.dwThreadId, pi.hThread);

    WaitForSingleObject(pi.hProcess, INFINITE);
    printf("(+) Process exiting!");

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return EXIT_SUCCESS;
}

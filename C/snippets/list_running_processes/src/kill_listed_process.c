#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h>
#include <string.h>


int main() {
    HANDLE hSnapshot;
    PROCESSENTRY32 pe32;

    while (true) {
        hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (hSnapshot == INVALID_HANDLE_VALUE) {
            return EXIT_FAILURE;
        }

        pe32.dwSize = sizeof(PROCESSENTRY32);

        if (!Process32First(hSnapshot, &pe32)) {
            printf("Failed to retrieve process information.\n");
            CloseHandle(hSnapshot);
            return EXIT_FAILURE;
        }

        while (true) {
            if (strcmp(strlwr(pe32.szExeFile), "taskmgr.exe") == 0) {
                printf("%s was opened but terminated with PID = %lu\n", pe32.szExeFile, pe32.th32ProcessID);

                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
                if (hProcess != NULL) {
                    TerminateProcess(hProcess, 0);
                    CloseHandle(hProcess);
                }
            }

            if (!Process32Next(hSnapshot, &pe32)) {
                break;
            }
        }
    }

    // Close the handle to the snapshot
    CloseHandle(hSnapshot);

    return EXIT_SUCCESS;
}

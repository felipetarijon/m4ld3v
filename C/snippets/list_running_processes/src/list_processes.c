#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>


int main() {
    HANDLE hSnapshot;
    PROCESSENTRY32 pe32;

    // Create a snapshot of the current processes
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        printf("Failed to create snapshot of processes.\n");
        return 1;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process in the snapshot
    if (!Process32First(hSnapshot, &pe32)) {
        printf("Failed to retrieve process information.\n");
        CloseHandle(hSnapshot);
        return 1;
    }

    // Print information about each process
    printf("PID\t\tProcess Name\n");
    printf("-------------------------------------\n");
    do {
        printf("%lu\t\t%s\n", pe32.th32ProcessID, pe32.szExeFile);
    } while (Process32Next(hSnapshot, &pe32));

    // Close the handle to the snapshot
    CloseHandle(hSnapshot);

    return 0;
}
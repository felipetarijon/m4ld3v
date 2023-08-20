#include <windows.h>
#include <Shlwapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void listDirRecursively(LPWSTR dirPath, LPCWSTR filePattern) {
    HANDLE hFind;
    WIN32_FIND_DATAW lpFindData;
    LARGE_INTEGER filesize;
    wchar_t szFullPattern[MAX_PATH];
    wchar_t *lpStr1;
    lpStr1 = szFullPattern;

    PathCombineW(szFullPattern, dirPath, filePattern);
    hFind = FindFirstFileW(szFullPattern, &lpFindData);

    do {
        if (lpFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // avoid "." and ".." directories
            if (wcscmp(lpFindData.cFileName, L".") == 0 || wcscmp(lpFindData.cFileName, L"..") == 0) {
                continue;
            }

            printf("dir: %ls/\n", lpFindData.cFileName);
            PathCombineW(szFullPattern, dirPath, lpFindData.cFileName);
            listDirRecursively(szFullPattern, filePattern);
        } else {
            filesize.LowPart = lpFindData.nFileSizeLow;
            filesize.HighPart = lpFindData.nFileSizeHigh;
            printf("file: %ls, size: %ld bytes\n", lpFindData.cFileName, filesize.QuadPart);
        }
    } while (FindNextFileW(hFind, &lpFindData) != 0);

    FindClose(hFind);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }

    char *mbString = argv[1];

    // Calculate the required buffer size for the wide-character string
    int bufferLength = MultiByteToWideChar(CP_UTF8, 0, mbString, -1, NULL, 0);
    if (bufferLength == 0) {
        perror("MultiByteToWideChar");
        return 1;
    }

    // Allocate memory for the wide-character string
    LPWSTR wcString = (LPWSTR)malloc(bufferLength * sizeof(wchar_t));
    if (wcString == NULL) {
        perror("malloc");
        return 1;
    }

    // Convert the multibyte string to wide-character string
    if (MultiByteToWideChar(CP_UTF8, 0, mbString, -1, wcString, bufferLength) == 0) {
        perror("MultiByteToWideChar");
        free(wcString);
        return 1;
    }

    listDirRecursively(wcString, L"*");

    // Clean up
    free(wcString);

    return EXIT_SUCCESS;
}

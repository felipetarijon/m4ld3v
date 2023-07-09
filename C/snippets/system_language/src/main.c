#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <Windows.h>


int main() {
    LANGID sysLanguageId = GetSystemDefaultUILanguage();
    LANGID usrLanguageId = GetUserDefaultUILanguage();
    WCHAR languageName[LOCALE_NAME_MAX_LENGTH];

    printf("System Language: %d\n", sysLanguageId);
    printf("User Language: %d\n", usrLanguageId);

    /*
    The following LCTypes can be used in the GetLocaleInfoW function below.

    LCType                           | Output
    ---------------------------------|-------------------------------
    LOCALE_SLOCALIZEDDISPLAYNAME    -> Portuguese (Brazil)
    LOCALE_SLOCALIZEDLANGUAGENAME   -> Portuguese
    LOCALE_SENGLISHLANGUAGENAME     -> Portuguese
    LOCALE_SNATIVELANGUAGENAME      -> portugu□s
    LOCALE_SLOCALIZEDCOUNTRYNAME    -> Brazil
    LOCALE_SENGLISHCOUNTRYNAME      -> Brazil
    LOCALE_SNATIVECOUNTRYNAME       -> Brasil
    LOCALE_IDIALINGCODE             -> 55
    LOCALE_SAM                      -> Empty (AM designator, eg "AM")
    LOCALE_SPM                      -> Empty (PM designator, eg "PM")
    */

    if (GetLocaleInfoW(sysLanguageId, LOCALE_SLOCALIZEDCOUNTRYNAME, languageName, LOCALE_NAME_MAX_LENGTH)) {
        printf("System Language: %ls\n", languageName);
    } else {
        printf("Failed to retrieve system language.\n");
    }

    // In case I don't want to run in Brazil
    if (wcscmp(L"Brazil", languageName) == 0) {
        ExitProcess(0);
    }

    // We can use the languages IDs as well
    if (sysLanguageId == 1046 || usrLanguageId == 1046) {
        ExitProcess(0);
    }

    return EXIT_SUCCESS;
}

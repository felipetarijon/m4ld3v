# HTTP(s) Requests

Provides ways to perform HTTP requests using different libraries.

## Dependencies

- MinGW32 or MinGW64 (it's up you). You can also use CygWin, but then your executable will depend on cygwin1.dll.

## Build

```bash
gcc -s -o winhttp src/winhttp.c -lwinhttp
```

Or to run the dynamic version:

```bash
gcc -s -o winhttp_dynamic src/winhttp_dynamic.c
```

## Run

```bash
./winhttp
# or
./winhttp_dynamic
```
# System Language

This snippet code provides ways to get the system's and user's respective languages (I live in Brazil, but my preferred language is English/en-us, so my system language is Portuguese and my user language is English). This feature is often implemented by different malware families to run only in an specific country or to avoid running in the CIS regions (like most ransomware).

## Dependencies

- MinGW32 or MinGW64 (it's up you). You can also use CygWin, but then your executable will depend on cygwin1.dll.

## Build

```bash
gcc -s -o syslang src/main.c
```

## Run

```bash
./syslang
```
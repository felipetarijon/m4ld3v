# Directory Listing

Implementation of directory listing on Windows. It lists a directory recursively
and prints the file's size and the directory name.

## Build

```bash
gcc -o dir-list .\src\win_dir_listing.c -lshlwapi
```

## Run

```
.\dir-list.exe "C:\\"
```

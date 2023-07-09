# C Language

You can find here what is necessary to build and run all the code located inside this "C" folder. Note that this is a general guideline. Each C project may have its own requirements. Therefore, read the README.md files inside of each project.

## Windows

On Windows, I recommend installing [MinGW](https://www.mingw-w64.org/downloads/#winlibscom). I downloaded (the one with GCC 13.1.0) both the x86 and x64 versions from this [link](https://winlibs.com/#download-release). Then, I extracted both of them at `C:\`, as `C:\mingw32` and `C:\mingw64`. You can set them as system's environment variables (`C:\mingwXX\bin`), but you'll have to choose one of them.  
  
Or you can use the full path whenever you need to execute gcc: 
  
```bash
C:\mingwXX\bin\gcc.exe -o program_name src/main.c
```
  
Yet, you can set up your IDE by creating different build configurations when you want to compile something for the x86 or x64 architectures.

## Linux

To do.
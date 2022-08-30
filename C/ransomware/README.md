# C Ransomware

This is part of the m4ld3v framework, an open-source project created for studying purposes.  
More information about the project at: https://github.com/felipetarijon/m4ld3v

## Dependencies

* <a href="https://github.com/rxi/log.c" target="_blank">log.c</a> to log stuff. It was cloned directly into libs/log and was added a custom CMakeLists.txt
* <a href="https://github.com/kokke/tiny-AES-c" target="_blank">tiny-AES-c</a> to handle cryptography. It was cloned directly into libs/aes

## Linux

### Requirements
* gcc
* cmake > 3.10 `sudo apt install cmake`

### Building and Running
  
1. Go to the build folder:  
`cd C/ransomware/build`

2. If "Error: could not load cache":  
`cmake ../`

3. Build the project:  
`cmake --build .`

4. Run:  
`bin/ransomware`
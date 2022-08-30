# M4LD3V 
M4lware D3velopment Framework FOR STUDYING PURPOSES

## About
This project was created initially to practice my programming language skills focused on cybersecurity, malware analysis, and reverse engineering. It's currently in its initial phase of development, focused on Linux OS and C language, but in the (near?) future it's going to be expanded to other platforms and languages.
  
**What is available so far?**
> Please remember that it's in the initial phase.

| Malware type | Language | Platform | Location     |
|--------------|----------|----------|--------------|
| Ransomware (**NOT WORKING YET!!!**)   | C        | Linux    | C/ransomware |
  

**Why use M4lD3V?**
* Build a custom malware sample to use during Red Team assesments.
* Practice your malware analysis and reverse engineering skills.
* Understand what an attacker can do to difficult analysis and avoid sandboxes.
* Have fun.

## Disclaimer
* Do not attempt to violate the law with anything contained here.
* Do not use the tool for illegal purposes. 
* The author(s) of this project is/are not responsible for any illegal actions.
* This project was created following <a href="https://docs.github.com/en/site-policy/acceptable-use-policies/github-active-malware-or-exploits" target="_blank">GitHub's acceptable policies</a>
* Read SECURITY.md

---

## How to Use

The framework is divided into programming languages folders.  
Each malware has its own folder and can be copied and built as an individual project.  
Therefore, depending on the language, the project has a different build system.  
So, each project has a README.md file with the instructions.

### Example - Building and Running a C Linux Ransomware
  
1. Go to the build folder:  
`cd C/ransomware/build`

2. If error "Error: could not load cache":  
`cmake ../`

3. Build the project:  
`cmake --build .`

4. Run:  
`bin/ransomware`

## Contributing
TO DO.
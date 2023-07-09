# M4LD3V 
M4lware D3velopment Collection **FOR STUDYING PURPOSES**

## About
This project was created initially to practice my programming language skills focused on operating systems internals, cybersecurity, malware analysis, and reverse engineering. It's currently in its initial phase of development, focused on C language, but in the future it's going to be expanded to other platforms and languages.
  
**What is available so far?**
> Please remember that it's in the initial phase.

### Malware

| Malware type | Language | Platform | Location     |
|--------------|----------|----------|--------------|
|To do   | -        | -    | - |
  
### Snippets

| Description | Language | Platform | Location     |
|--------------|----------|----------|--------------|
| HTTP Requests | C        | Linux \| Windows    | C/snippets/http_requests |
| List running processes | C        | Linux \| Windows    | C/snippets/list_running_processes |
| Detect OS language | C        | Linux \| Windows    | C/snippets/system_language |

### Studies

This is for malware development courses/series and studies I may take along the way. The idea is to take useful notes and practice some things like exercises and important concepts.

| Name | Language(s) | Platform(s) | Location     |
|--------------|----------|----------|--------------|
| [Crow's Nest](https://crows-nest.gitbook.io/crows-nest/malware-development/getting-started-with-malware-development)   | C/C++        | Windows    | studies/crows-nest |

### Techniques

| Name | Language | Platform | Location     |
|--------------|----------|----------|--------------|
| Auto Start Execution | C        | Linux \| Windows    | C/techniques/T1547/001 |

**Why use M4lD3V?**
* Build a custom malware sample to use during Red Team assessments.
* Practice your malware analysis and reverse engineering skills.
* Study Operating Systems and AVs Internals.
* Study malware development techniques.
* Understand what an attacker can do to difficult analysis and avoid sandboxes.
* Test and master your day-to-day tools against the samples.
* Have fun.

## Disclaimer
* Do not attempt to violate the law with anything contained here.
* Do not use the tool for illegal purposes. 
* The author(s) of this project is/are not responsible for any illegal actions.
* This project was created following <a href="https://docs.github.com/en/site-policy/acceptable-use-policies/github-active-malware-or-exploits" target="_blank">GitHub's acceptable policies</a>
* Read SECURITY.md

---

## How to Use

The project is divided into programming languages' folders and these folders may have a ".templates" folder containing different templates for the given programming language. The objective with that is to help with the development of new malware for the given programming language.  
  
Each malware has its own folder and can be copied and built as an individual project. Therefore, depending on the language, the project has a different build system (e.g, using cmake, make, or gcc).  
  
So, each project has a README.md file with its instructions.

### Example - Building and Running a C Snippet
  
1. Go to the snippet folder:  
`cd C/snippets/system_language`

2. Build the output file:  
`gcc -s -o syslang src/main.c`

3. Run:  
`./syslang`

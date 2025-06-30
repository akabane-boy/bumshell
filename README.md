# bumshell

**bumshell** is a simple Unix-like shell written in C.

## Functionality
- Reads input using getline()
- Skips blank input or whitespace-only input
- Tokenizes command up to 32 arguments
- Executes external commands using fork() and execvp() system calls

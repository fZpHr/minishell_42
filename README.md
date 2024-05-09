## This project was a collaborative one, and my teammate was https://github.com/gnoumalin.

## Minishell

Minishell is a 42 project where you create a simple shell program capable of interpreting and executing basic shell commands. The goal is to implement a miniature version of the UNIX shell, allowing users to interact with the system through a command-line interface. This project helps reinforce your understanding of process management, system calls, and command parsing.

*For more information, please refer to the subject in the git.*

## Installation

To install Minishell, clone the project from the Git repository:

```bash
git clone git@github.com:fZpHr/minishell_42.git
cd minishell_42
```

Then compile the executable using the provided Makefile:

```bash
make
```

## Usage

To run Minishell, execute the following command:

```bash
./minishell
```

### Basic Command Execution

You can execute basic shell commands such as `ls`, `pwd`, or `echo`:

```bash
ls
```

```bash
pwd
```

```bash
echo "Hello, world!"
```

### Input/Output Redirection

Minishell supports input/output redirection:

```bash
echo "Hello, world!" > output.txt
```

```bash
cat < input.txt
```

### Pipes

You can use pipes to chain multiple commands together:

```bash
ls | grep "file"
```

### Built-in Commands

Minishell supports built-in commands:

- `cd`: Change directory.
- `export`: Set environment variables.
- `unset`: Unset environment variables.
- `env`: Display environment variables.
- `pwd`: Print current working directory.
- `exit`: Exit Minishell.

### Here Document (Heredoc)

You can use heredoc to redirect input from the current command line:

```bash
<< END_OF_INPUT
This is a heredoc example.
It allows multiline input until the specified delimiter.
END_OF_INPUT
```
### Signals

Minishell handles signals such as Ctrl+C (SIGINT) and Ctrl+D (EOF):

- Ctrl+C: Interrupts the current command and returns to the shell prompt.
- Ctrl+D: Indicates end-of-file (EOF) or closes the input stream if used with an empty command line, exiting Minishell.

## Description

The program will start a new shell session, allowing the user to enter commands and interact with the system. Minishell reproduces basic shell behavior, supporting functionalities such as executing external commands, handling built-in commands, managing environment variables, and supporting input/output redirection.

# Simple Shell

A simple UNIX command line interpreter written in C.

This shell reads user input, tokenizes the command, checks if the command is a built-in, resolves executable paths using `PATH`, then runs commands using `fork()` and `execve()`.

## Compilation

To compile the program, run:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

To run the shell interactively:

```bash
./hsh
```

Example:

```bash
$ ./hsh
$ ls
$ pwd
$ echo hello
$ exit
```

The shell also supports non-interactive mode:

```bash
echo "ls" | ./hsh
```

## Built-in Commands

| Command | Description |
|---|---|
| `exit` | Exits the shell |
| `exit [status]` | Exits the shell with a specific status code |
| `env` | Prints the current environment variables |
| `setenv NAME VALUE` | Creates or updates an environment variable |
| `unsetenv NAME` | Removes an environment variable |

## Example Usage

### Run a command

```bash
$ ls
```

### Run a command with arguments

```bash
$ ls -l /tmp
```

### Print environment variables

```bash
$ env
```

### Set an environment variable

```bash
$ setenv NAME Ben
```

### Remove an environment variable

```bash
$ unsetenv NAME
```

### Exit the shell

```bash
$ exit
```

## How the Shell Works

```text
+----------------------+
|      Start shell     |
+----------+-----------+
           |
           v
+----------------------+
|   Display prompt $   |
|  interactive only    |
+----------+-----------+
           |
           v
+----------------------+
|   Read input line    |
+----------+-----------+
           |
           v
+----------------------+
|    Tokenize input    |
|  command + arguments |
+----------+-----------+
           |
           v
+----------------------+
|  Is it a built-in?   |
+------+---------------+
       |
       +---- Yes ----+
       |             v
       |   +----------------------+
       |   | Run built-in command |
       |   +----------+-----------+
       |              |
       |              v
       |   +----------------------+
       |   | Return to prompt     |
       |   +----------------------+
       |
       No
       |
       v
+----------------------+
| Search command path  |
| using PATH variable  |
+----------+-----------+
           |
           v
+----------------------+
|  Command found?      |
+------+---------------+
       |
       +---- No -----+
       |             v
       |   +----------------------+
       |   | Print error message  |
       |   +----------+-----------+
       |              |
       |              v
       |   +----------------------+
       |   | Return to prompt     |
       |   +----------------------+
       |
       Yes
       |
       v
+----------------------+
|        fork()        |
+----------+-----------+
           |
           v
+----------------------+
| Child runs execve()  |
+----------+-----------+
           |
           v
+----------------------+
| Parent waits         |
| using wait()         |
+----------+-----------+
           |
           v
+----------------------+
| Return to prompt     |
+----------------------+
```

## Project Files

| File | Purpose |
|---|---|
| `main.c` | Entry point of the shell |
| `cmd.c` | Handles built-in command dispatching |
| `exec.c` | Handles process creation and command execution |
| `path.c` | Resolves command paths using `PATH` |
| `tokens.c` | Splits user input into command arguments |
| `env.c` | Handles environment variable logic |
| `utils.c` | Contains helper functions |
| `shell.h` | Main header file with prototypes and includes |

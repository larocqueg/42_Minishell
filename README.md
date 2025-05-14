#  Minishell

Welcome to our custom shell — **Minishell**, a simplified version of the Unix shell written in C for the 42 school project.

> **The goal?** Rebuild core features of a real shell, from parsing commands and handling redirections to implementing key built-ins.

---

###  What It Can Do

Minishell supports:

- **Command execution** (e.g. `ls`, `cat`, etc.)
- **Redirections**:
  - Output: `>` and `>>`
  - Input: `<` and `<<` (heredoc)
- **Pipes** (`|`) to connect commands
- **Built-in commands**:
  - `echo`
  - `cd`
  - `env`
  - `export`
  - `unset`
  - `pwd`
  - `exit`
- **Wildcard expansion (`*`)** — *bonus part only!*
  - Works in the **current directory** (e.g., `cat *.c`)

---

###  How to Try It

```bash
git clone https://github.com/yourusername/minishell.git
cd minishell
make
./minishell
```

You’ll see the prompt:

```shell
minishell $<
```

Start typing your commands like you would in bash!

---

### Some Examples

```shell
minishell$ echo Hello World > hello.txt
minishell$ cat < hello.txt | grep Hello
Hello World
```

```shell
minishell$ cat << EOF
> line 1
> line 2
> EOF
line 1
line 2
```

---

###  Bonus Part

We implemented **wildcard expansion (`*`)** — for the current folder only.

So things like this work just fine:

```shell
minishell$ ls *.c
main.c parsing.c utils.c
```

---

### ⚙ Project Structure

```
.
├── Makefile
├── mandatory/
│   ├── includes/
│   │   └── minishell.h
│   └── srcs/
│       ├── builtin/         # Built-in commands (cd, echo, etc.)
│       ├── cli/             # Prompt handling
│       ├── env/             # Environment variable logic
│       ├── execute/         # Execution, redirections, pipes
│       ├── free_utils/      # Memory cleanup helpers
│       ├── parsing/         # Tokenization, heredoc, syntax checks
│       ├── signals/         # Signal handling (Ctrl-C, etc.)
│       └── main.c
├── bonus/
│   ├── includes/
│   │   └── minishell_bonus.h
│   └── srcs/
│       ├── builtin/         # Bonus version of built-ins
│       ├── cli/             # Prompt handling
│       ├── env/             # Environment logic
│       ├── execute/         # Execution logic with wildcard support
│       ├── free_utils/      # Memory cleanup
│       ├── parsing/         # Tokenizing and expanding
│       ├── signals/         # Signal handling
│       └── main_bonus.c
```

---

###  Authors

- Gabriel La Rocque ([gde-la-r](https://github.com/larocqueg))  
- Rafael Castro ([rafaelfe](https://github.com/therappha))

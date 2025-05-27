# minishell

![Language](https://img.shields.io/badge/Language-C-yellow)
![Build](https://img.shields.io/badge/Build-Makefile-blue)
![Status](https://img.shields.io/badge/Status-Prototype-orange)

## 📖 Overview

**minishell** is a simple, POSIX-compliant shell built in C as part of the 42/1337 School curriculum. It supports basic command execution, environment management, redirections, and a set of built-in commands—all implemented from scratch. This project deepens your understanding of:

- Parsing and tokenizing shell input
- Process creation and control (`fork` / `execve`)
- Programmatic I/O redirection and here-docs
- Signal handling
- Environment variable management

---

## ✨ Features

### Built-in Commands
- `cd`      — Change current working directory  
- `echo`    — Print arguments to standard output  
- `env`     — Display the environment  
- `export`  — Add or modify environment variables  
- `unset`   — Remove variables from the environment  
- `pwd`     — Print working directory  
- `exit`    — Exit the shell  

### Parsing & Execution
- **Word splitting**  
- **Quoting**: single (`'`) and double (`"`)  
- **Environment expansion**: `$VAR`  
- **Redirections**: `<`, `>`, `>>`, `<<` (here-doc)  
- **Piping**: connect multiple commands with `|`  
- **PATH resolution**: search executables in `PATH`  

### Technical Highlights
- **Line editing & history** via GNU Readline  
- **Linked list** based environment storage  
- **Robust error handling** (invalid syntax, exec failures)  
- **Signal management**: `Ctrl-C`, `Ctrl-\`, `Ctrl-D`  

---

## 🛠️ Technical Stack

- **Language**: C (C99 / POSIX)  
- **Build**: Makefile  
- **Libraries**:  
  - [libft](https://github.com/Marouane0107/minishell/tree/main/mini/libft) (custom utility library)  
  - GNU Readline (`-lreadline`)  
- **Tools**: GCC, AddressSanitizer (`-fsanitize=address`)  

---

## 🚀 Getting Started

### Prerequisites

- Unix-like OS (Linux, macOS)  
- `gcc` or `clang` compiler  
- `make` utility  
- `readline` development headers (e.g., `libreadline-dev`)

### Installation

```bash
# Clone repo
git clone https://github.com/Marouane0107/minishell.git
cd minishell/mini

# Build libft and minishell
make

# Build artifacts:
# - libft/libft.a
# - minishell executable
```

### Cleaning

```bash
make clean    # Remove object files
make fclean   # Remove object files, libft.a, and executable
make re       # fclean + all
```

---

## 🖥️ Usage

```bash
./minishell
```

You’ll see a prompt like:

```
minishell$ 
```

Try commands:

```shell
# External command
minishell$ ls -la /tmp

# Built-ins
minishell$ pwd
/home/user/minishell/mini

minishell$ export MYVAR=42
minishell$ env | grep MYVAR

minishell$ cd /usr/local
minishell$ pwd

minishell$ echo "Hello, World!"

# Here-document
minishell$ cat << EOF
> This is line 1
> This is line 2
> EOF

# Pipeline
minishell$ echo "foo\nbar" | grep ba
```

Press `Ctrl-D` or type `exit` to quit.

---

## 📁 Project Structure

```
minishell/
├── en.subject.pdf           # Project specification
├── builtins/                # Built-in command implementations
│   ├── cd.c
│   ├── echo.c
│   ├── env.c
│   ├── exit.c
│   ├── export.c
│   ├── pwd.c
│   └── unset.c
└── mini/                    # Shell sources & build
    ├── Makefile             # Build configuration
    ├── main.c               # Entry point & main loop
    ├── parss.c              # Input parsing & tokenization
    ├── excution.c           # Command execution logic
    ├── openherd.c           # Here-doc support
    ├── utils*.c             # Utility functions
    ├── linkd_list.c         # Environment storage
    ├── get_env.c            # Env var handling
    ├── changing_files.c     # Directory change logic
    ├── free.c               # Cleanup routines
    └── libft/               # Custom C utility library
        └── [libft sources]
```

---

## 🧪 Testing & Validation

- **Functional tests**: try each built-in, command combinations, edge cases  
- **Syntax errors**: unmatched quotes, invalid redirections  
- **Signal tests**: `Ctrl-C` during prompt or execution  
- **Memory checks**: run under AddressSanitizer  

---

## 🤝 Contributing

1. Fork this repository  
2. Create a branch: `git checkout -b feature/your-feature`  
3. Commit your changes: `git commit -m "Add feature"`  
4. Push: `git push origin feature/your-feature`  
5. Open a Pull Request  

---

## 📚 Resources

- [minishell subject (PDF)](./en.subject.pdf)  
- [GNU Readline Manual](https://tiswww.case.edu/php/chet/readline/readline.html)  
- [POSIX execve documentation](https://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html)  
- [42 School Documentation](https://github.com/42School)

---

## 👨‍💻 Author

**Marouane0107**  
https://github.com/Marouane0107

---

*Built as part of 42/1337 School curriculum.*  

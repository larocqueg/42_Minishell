/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:44:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/30 19:04:16 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libs/libft/libft.h"

#include <stdio.h>        // for printf(), strerror(), perror()
#include <stdlib.h>       // for malloc(), free(), exit(), getenv()
#include <unistd.h>       // for write(), access(), open(), read(), close(), getcwd(), chdir(), execve(), dup(), dup2(), pipe(), isatty(), ttyname(), ttyslot()
#include <sys/types.h>    // for types like pid_t, etc.
#include <sys/wait.h>     // for wait(), waitpid(), wait3(), wait4()
#include <signal.h>       // for signal(), sigaction(), sigemptyset(), sigaddset(), kill()
#include <sys/stat.h>     // for stat(), lstat(), fstat()
#include <fcntl.h>        // for file flags with open()
#include <dirent.h>       // for opendir(), readdir(), closedir()
#include <sys/ioctl.h>    // for ioctl()
#include <termios.h>      // for tcsetattr(), tcgetattr()
#include <term.h>         // for tgetent(), tgetflag(), tgetnum(), tgetstr(), tgoto(), tputs()
#include <readline/readline.h>  // for readline()
#include <readline/history.h>   // for rl_clear_history(), rl_on_new_line(), rl_replace_line(), rl_redisplay(), add_history()
#include <stdbool.h>

#define GIT_HEAD_FILE ".git/HEAD"
#define START_GIT BOLD GREEN"git:("RESET
#define END_GIT BOLD GREEN") "RESET
//#define PROGRAM_NAME GREEN"➜  "RESET BOLD
#define PROGRAM_NAME BOLD RED" minihellv1 ➜ "RESET BOLD //minihell
#define RESET "\033[0m"
#define RED "\033[31m"
#define WHITE "\033[37m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"
#define BOLD "\033[1m"
#define BLACK "\033[30m"

//functions
int	check_cmd(char **cmd, char **envp);
#endif

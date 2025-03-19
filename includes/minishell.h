/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:44:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/19 11:45:03 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// for printf(), strerror(), perror()
# include <stdio.h>
// for malloc(), free(), exit(), getenv()
# include <stdlib.h>
// for write(), access(), open(), read(), close(), getcwd(), chdir(), execve(), dup(), dup2(), pipe(), isatty(), ttyname(), ttyslot()  
# include <unistd.h>
// for types like pid_t, etc.     
# include <sys/types.h>
// for wait(), waitpid(), wait3(), wait4()    
# include <sys/wait.h>
// for signal(), sigaction(), sigemptyset(), sigaddset(), kill()
# include <signal.h>
// for stat(), lstat(), fstat()
# include <sys/stat.h>
// for file flags with open()
# include <fcntl.h>
// for opendir(), readdir(), closedir()
# include <dirent.h>
// for ioctl()
# include <sys/ioctl.h>
// for tcsetattr(), tcgetattr()
# include <termios.h>
// for tgetent(), tgetflag(), tgetnum(), tgetstr(), tgoto(), tputs()
# include <term.h>
// for readline()
# include <readline/readline.h>
// for rl_clear_history(), rl_on_new_line(), rl_replace_line(), rl_redisplay(), add_history()
# include <readline/history.h>

int	ft_putstr_fd(char *str, int fd);
int	ft_putstr(char *str);

#endif

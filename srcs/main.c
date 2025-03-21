/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:06:52 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/21 10:33:35 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		//rl_redisplay();
	}
}

char	*append_cmd(char *path, char *cmd)
{
	char	*temp;

	temp = ft_strjoin(path, cmd);
	free(path);
	return (temp);
}
char	*check_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);

	while(envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			return (envp[i]);
		}
		i++;
	}
	return (NULL);
}

char **ft_split_path(char *env_path, char *cmd)
{
	char	**split_path;
	char	*slashcmd;
	int	i;

	slashcmd = ft_strjoin("/", cmd);
	split_path = ft_split(env_path, ':');
	i = 0;
	while (split_path[i])
	{
		split_path[i] = append_cmd(split_path[i], slashcmd);
		i++;
	}
	free(slashcmd);
	return (split_path);

}

char *check_cmdpath(char **split_path, char **pwdpath)
{
	int		i;
	char	*valid_path;

	valid_path = NULL;
	i = 0;
	while (split_path && split_path[i])
	{
		if (access(split_path[i], F_OK | X_OK) == 0)
			valid_path = split_path[i];
		i++;
	}
	if (!valid_path)
	{
		i = 0;
		while (pwdpath[i])
		{
			if (access(pwdpath[i], F_OK | X_OK) == 0)
				valid_path = pwdpath[i];
			i++;
		}
	}
	return (valid_path);
}

int	only_spaces(char *str)
{
	while(*str)
	{
		if (*str != 32 && !(*str >= 9 && *str <= 13))
			return (0);
		str++;
	}
	return (1);
}

void	handle_prompt(char *prompt, char **envp)
{
		char	*path;
		char	*pwd;
		char **cmd;
		char **split_path;
		char **pwdpath;

		int pid;
		if (prompt == NULL || prompt[0] == '\0' || only_spaces(prompt))
			return;
		pwd = NULL;
		split_path = NULL;
		cmd = ft_split(prompt, ' ');
		pwd = getcwd(pwd, 4096);
		if (check_cmd(cmd, envp))
			return ;
		pid = fork();

		if (pid != 0)
		{
			waitpid(pid, NULL, 0);
			return ;
		}
		path = check_envp(envp);
		if (path)
		{
			split_path = ft_split_path(path, cmd[0]);
		}
		pwdpath = ft_split_path(pwd, cmd[0]);
		path = check_cmdpath(split_path, pwdpath);
		if (!path)
		{

			ft_printf("testshell: %s: command not found\n", cmd[0]);
			exit(1);
		}
		else
			execve(path, cmd, envp);

}

char	*get_git(char *str)
{
	int	git_fd;
	char *headline;
	char *temp;
	char *temp2;
	char *branch_line;
	char *return_line;
	char *git_name;

	(void)str;
	git_fd = -1;
	git_name = ft_strdup(GIT_HEAD_FILE);
	for(int i = 0; i < 10; i++)
	{
		git_fd = open(git_name, O_RDONLY);
		if (git_fd != -1)
		{
			free(git_name);
			break;
		}
		temp2 = ft_strjoin("../", git_name);
		free(git_name);
		git_name = temp2;
	}
	if (git_fd == -1)
		return (NULL);
	headline = get_next_line(git_fd);
	if (!headline)
		return (NULL);
	branch_line = ft_strjoin(RED, BOLD);
	temp = ft_strrchr(headline, '/');
	temp = ft_strtrim(temp, "\n");
	return_line = ft_strjoin(branch_line, temp + 1);
	free(headline);
	free(temp);
	branch_line = ft_strjoin(return_line, RESET);
	free(return_line);
	temp = ft_strjoin(START_GIT, branch_line);
	headline = ft_strjoin(temp, END_GIT);
	return_line = ft_strjoin(str, headline);
	free(temp);
	free(headline);
	return (return_line);

}
char *get_cli_pwd(void)
{
	char	*pwd;
	char	*cli_str;
	char	*temp;
	char	*str;

	pwd = getcwd(NULL, 4096);
	if ((ft_strncmp(getenv("HOME"), pwd, ft_strlen(pwd)) == 0) &&
		ft_strlen(getenv("HOME")) == ft_strlen(pwd))
	{
		//cli_str = ft_strdup(CYAN"~ $< "RESET); //minihell
		cli_str = ft_strdup(CYAN"~  "RESET); //zsh theme
	}
	else
	{
		temp = ft_strrchr(pwd, '/'); //zsh theme
		if (ft_strncmp("/home", pwd, 5) == 0 && ft_strlen(pwd) > 5)
			temp = temp + 1;
		temp = ft_strjoin(CYAN, temp); //zsh theme
		cli_str = ft_strjoin(temp, " "RESET); //zsh theme
		free(temp);
		//cli_str = ft_strjoin(temp + 1, " $< "); minihell
	}

	str = ft_strjoin(PROGRAM_NAME, cli_str);
	temp = get_git(str);
	if (temp)
	{
		free(str);
		str = temp;
	}
	free(cli_str);
	free(pwd);
	return (str);
}
int	main(int ac, char *av[], char **envp)
{
	char	*prompt;
	char	*name;

	signal(SIGINT, signal_handler);
	(void)ac;
	(void)av;

	while (1)
	{
		name = get_cli_pwd();
		prompt = readline(name);
		if (prompt != NULL && !only_spaces(prompt))
			add_history(prompt);
		free(name);
		handle_prompt(prompt, envp);
	}

}

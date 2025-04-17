/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:00:07 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/17 18:00:59 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	put_export(char *str)
{
	int		i;
	bool	equal;

	equal = false;
	i = 0;
	ft_printf("declare -x ");
	while (str[i])
	{
		if (str[i] == '=' && !equal)
		{
			equal = true;
			write(1, &str[i++], 1);
			write(1, "\"", 1);
		}
		else
			write(1, &str[i++], 1);
	}
	if (equal)
		write(1, "\"", 1);
	write(1, "\n", 1);
}

void	print_export(t_shell *sh)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	temp = clone_envp(sh, sh->envp);
	while (temp[i])
	{
		j = i + 1;
		while (temp[j])
		{
			if (ft_strcmp_tochar(temp[i], temp[j], '=') > 0)
				ft_swap(&temp[i], &temp[j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (temp[i])
	{
		put_export(temp[i]);
		free(temp[i++]);
	}
	free(temp);
	return ;
}

static int	is_valid_var(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		i++;
	}
	if (!str[i] || (str[i] && str[i] == '='))
		return (1);
	else
		return (0);
}

static int	ft_strcmp_export(char **env, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	while(env[i])
	{
		j = 0;
		while ((env[i][j] && cmd[j]) && env[i][j] == cmd[j])
		{
			j++;
		}
		if ((!env[i][j] || env[i][j] == '=') && cmd[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void	create_export(char *str, t_shell *sh)
{
	char	*var_name;
	char	*no_equal;
	char	*no_quotes;
	bool	equals;
	int		i;

	i = 0;
	equals = false;
	while (str[i])
	{
		if (str[i] == '=')
		{
			equals = true;
			break;
		}
		i++;
	}
	no_quotes = remove_quotes(str);
	str = no_quotes;
	no_equal = ft_strndupmod(str, 0, ft_strlen_tochar(str, '=') - 1);
	var_name = ft_strndupmod(str, 0, ft_strlen_tochar(str, '='));
	if (ft_strcmp_export(sh->envp, no_equal))
	{
		if (equals)
			ft_change_var(var_name, str + ft_strlen_tochar(var_name, '=') + 1, sh->envp);
	}
	else
	{
		sh->envp = append_cmd(sh->envp, str);
		sh->env_size++;
	}
	free(no_equal);
	free(no_quotes);
	free(var_name);
	ft_exit_status(0, 1, 0);
}

int	is_append_var(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		i++;
	}
	if (str[i] == '+')
		i++;
	if (str[i] == '=')
		return (1);
	else
		return (0);
}

void	append_var(char *var, t_shell *sh)
{
	int		i;
	char 	*temp;
	char	*var_name;
	char	*value;
	i = 0;

	var_name = ft_strndupmod(var, 0, ft_strlen_tochar(var, '+') - 1);
	temp = ft_get_env(var_name, sh->envp);
	if (!temp)
	{
		value = (ft_strjoin(var_name, "="));
		if (!value)
			return ;
		temp = ft_strjoin(value, var + ft_strlen_tochar(var, '=') + 1);
		if (!temp)
			return ;
		ft_fprintf(2, "temp == '%s'\n", temp);
		create_export(temp, sh);
		free(value);
		free(temp);
		return ;
	}
	else
	{
		value = ft_strjoin(temp, var + ft_strlen_tochar(var, '=') + 1);
		if (!value)
			return ;
		ft_fprintf(2, "var == %s, value == '%s'\n", var, value);
		temp = ft_strjoin(var_name, "=");
		if (!temp)
			return ;
		free(var_name);
		var_name = ft_strjoin(temp, value);
		if (!var_name)
			return ;
		ft_fprintf(2, "var_name == '%s'\n", var_name);
		create_export(var_name, sh);
		free(temp);
		free(value);
		free(var_name);
		return ;
	}
}

void	exec_export(t_shell *sh, t_cmd *cmd)
{
	char	**cmds;
	int		i;

	i = 1;
	cmds = cmd->cmd;
	if (cmds[1] == NULL)
	{
		print_export(sh);
		ft_exit_status(0, 1, 0);
	}
	else
	{
		while (cmds[i])
		{
			if (is_valid_var(cmds[i]) || is_var(cmds[i]))
				create_export(cmds[i], sh);
			else if (is_append_var(cmds[i]))
			{
				append_var(cmds[i], sh);
				ft_exit_status(0, 1, 0);
			}
			else
			{
				ft_fprintf(2, "export: '%s': not a valid identifier\n", cmds[i]);
				ft_exit_status(1, 1, 0);
			}
			i++;
		}
	}
}

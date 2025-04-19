/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:00:07 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/17 22:13:11 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	print_export(t_shell *sh)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	if (sh->env_size == 0)
		return ;
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
	ft_free_export(temp);
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

int	ft_strcmp_export(char **env, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
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
	int		i;

	i = 0;
	no_quotes = remove_quotes(str);
	str = no_quotes;
	no_equal = ft_strndupmod(str, 0, ft_strlen_tochar(str, '=') - 1);
	var_name = ft_strndupmod(str, 0, ft_strlen_tochar(str, '='));
	if (ft_strcmp_export(sh->envp, no_equal))
	{
		if (has_equals(str))
			ft_change_var(var_name, str
				+ ft_strlen_tochar(var_name, '=') + 1, sh->envp);
	}
	else
	{
		sh->envp = append_cmd(sh->envp, str);
		sh->env_size++;
	}
	free(no_equal);
	free(no_quotes);
	free(var_name);
	ft_exit(0, 1, 0);
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
		ft_exit(0, 1, 0);
	}
	else
	{
		while (cmds[i])
		{
			ft_exit(1, 1, 0);
			if (is_valid_var(cmds[i]) || is_var(cmds[i]))
				create_export(cmds[i], sh);
			else if (is_append_var(cmds[i]))
				do_append(cmds[i], sh);
			else
				ft_fprintf(2, "export: '%s': %s\n", cmds[i], INVALID_I);
			i++;
		}
	}
}

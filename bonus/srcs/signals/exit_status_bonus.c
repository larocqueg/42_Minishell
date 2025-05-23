/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:06:50 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/22 18:26:16 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	ft_exit(int exit_code, bool set, bool close)
{
	static int	exit_status;

	if (set)
		exit_status = exit_code;
	if (close)
		exit (exit_status);
	return (exit_status);
}

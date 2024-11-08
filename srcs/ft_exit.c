/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:54:46 by rkhatim           #+#    #+#             */
/*   Updated: 2024/10/30 13:56:42 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	two_many_arguments(int *exit_status, t_cmd *cmd, char **cmd_arguments)
{
	*exit_status = 1;
	if (is_valid_number(cmd_arguments[1]) && is_valid_number(cmd_arguments[2]))
	{
		printf("bash: exit: too many arguments\n");
		if (cmd->next || cmd->prev)
			exit(1);
		else
			return ;
	}
	if (!is_valid_number(cmd_arguments[1]))
	{
		printf("bash: exit: %s: numeric argument required\n",
			cmd_arguments[1]);
		exit(255);
	}
	if (!is_valid_number(cmd_arguments[2]))
	{
		printf("bash: exit: %s: too many arguments\n",
			cmd_arguments[2]);
		if (cmd->next || cmd->prev)
			exit(1);
		else
			return ;
	}
}

void	ft_exit(t_cmd *cmd)
{
	printf("exit\n");
	if (cmd->arguments[1] && !is_valid_number(cmd->arguments[1]))
	{
		g_main.exit_status = 2;
		printf("bash: exit: %s: numeric argument required", cmd->arguments[1]);
		exit(g_main.exit_status);
	}
	if (cmd->arguments[2] && cmd->arguments[1])
		return (two_many_arguments(&g_main.exit_status, cmd, cmd->arguments));
	if (!cmd->arguments[1])
		exit(0);
	else
	{
		if (cmd->arguments[1][0] == '-')
		{
			g_main.exit_status = 256 - ft_atoi(cmd->arguments[1] + 1);
			exit(g_main.exit_status);
			// check if it is working 
		}
		else
		{
			g_main.exit_status = ft_atoi(cmd->arguments[1]);
			exit(g_main.exit_status);
		}
	}
}

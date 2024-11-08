/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhatim <rkhatim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:53:37 by rkhatim           #+#    #+#             */
/*   Updated: 2024/11/06 14:10:55 by rkhatim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_cmd *cmd_list)
{
	if (!ft_strncmp(cmd_list->arguments[0], "echo", 4)
		&& (ft_strlen(cmd_list->arguments[0]) == 4))
		return (1);
	else if (!ft_strncmp(cmd_list->arguments[0], "cd", 2)
		&& (ft_strlen(cmd_list->arguments[0]) == 2))
		return (1);
	else if (!ft_strncmp(cmd_list->arguments[0], "pwd", 3)
		&& (ft_strlen(cmd_list->arguments[0]) == 3))
		return (1);
	else if (!ft_strncmp(cmd_list->arguments[0], "env", 3)
		&& (ft_strlen(cmd_list->arguments[0]) == 3))
		return (1);
	else if (!ft_strncmp(cmd_list->arguments[0], "exit", 4)
		&& (ft_strlen(cmd_list->arguments[0]) == 4))
		return (1);
	else if (!ft_strncmp(cmd_list->arguments[0], "unset", 5)
		&& (ft_strlen(cmd_list->arguments[0]) == 5))
		return (1);
	else if (!ft_strncmp(cmd_list->arguments[0], "export", 6)
		&& (ft_strlen(cmd_list->arguments[0]) == 6))
		return(1);
	return (0);
}

void	excute_builtin(t_cmd *cmd_list)
{
	if (!ft_strncmp(cmd_list->arguments[0], "echo", 4)
		&& (ft_strlen(cmd_list->arguments[0]) == 4))
		ft_echo(cmd_list);
	else if (!ft_strncmp(cmd_list->arguments[0], "cd", 2)
		&& (ft_strlen(cmd_list->arguments[0]) == 2))
		cd(cmd_list);
	else if (!ft_strncmp(cmd_list->arguments[0], "pwd", 3)
		&& (ft_strlen(cmd_list->arguments[0]) == 3))
		ft_pwd();
	else if (!ft_strncmp(cmd_list->arguments[0], "env", 3)
		&& (ft_strlen(cmd_list->arguments[0]) == 3))
		my_env();
	else if (!ft_strncmp(cmd_list->arguments[0], "exit", 4)
		&& (ft_strlen(cmd_list->arguments[0]) == 4))
		ft_exit(cmd_list);// done but leaks still not checked
	else if (!ft_strncmp(cmd_list->arguments[0], "unset", 5)
		&& (ft_strlen(cmd_list->arguments[0]) == 5))
		unset(cmd_list);
	else if (!ft_strncmp(cmd_list->arguments[0], "export", 6)
		&& (ft_strlen(cmd_list->arguments[0]) == 6))
		export(cmd_list);
}


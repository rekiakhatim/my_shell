/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:54:26 by rkhatim           #+#    #+#             */
/*   Updated: 2024/10/20 18:49:04 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_option(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-' && arg[1] == 'n')
	{
		i++;
		while (arg[i] == 'n')
			i++;
		if (arg[i] == '\0')
			return (1);
	}
	return (0);
}

int	get_last_n_option(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->arguments[i])
	{
		if (is_n_option(cmd->arguments[i]))
			i++;
		else
			break ;
	}
	return (i);
}

void	check_if_we_should_print_nl(t_cmd *cmd, int *should_print_nl)
{
	int	i;

	i = 1;
	while (cmd->arguments[i])
	{
		if (is_n_option(cmd->arguments[i]))
			*should_print_nl = 0;
		else
			break ;
		i++;
	}
	if (!*should_print_nl)
		i = get_last_n_option(cmd);
	while (cmd->arguments && cmd->arguments[i])
	{
		printf("%s", cmd->arguments[i++]);
		if(cmd->arguments[i])
			printf(" ");
	}
}

void	ft_echo(t_cmd *cmd)
{
	int	should_print_nl;
	
	should_print_nl = 1;

	if (!cmd || !cmd->arguments)
		return ;
	check_if_we_should_print_nl(cmd, &should_print_nl);
	if (should_print_nl)
		printf("\n");
	g_main.exit_status = 0;
}

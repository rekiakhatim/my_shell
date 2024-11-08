/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhatim <rkhatim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:34:30 by hboustaj          #+#    #+#             */
/*   Updated: 2024/11/07 16:03:13 by rkhatim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_main g_main;

int	main(void)
{
	char	*input;
	t_info	*data;
	t_cmd	*command;

	env_dup();
	while (1)
	{
		data = ft_calloc(sizeof(t_info), 1);
		data->tokens = NULL;
		input = readline("minishell$ ");
		if (!input)
			free(data);
		if (!input)
			break ;
		if (!input[0])
			free(data);
		if (!input[0])
			continue ;
		add_history(input);
		command = parse_input(data, input);
		if(!command)
			continue;
		// print_list(command);
		exec(command);
		ft_free(data, command);
		//g_main.exit_status = 0;
	}
	return (0);
}

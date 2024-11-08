/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:07:05 by hboustaj          #+#    #+#             */
/*   Updated: 2024/10/13 18:01:03 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_khrej(char *str, int nb)
{
	g_main.exit_status = nb;
	printf("%s\n", str);
}

bool	invalid_pipe(t_lexer *token)
{
	t_lexer	*ptr;

	ptr = token;
	while (ptr)
	{
		if ((ptr->previous == NULL || ptr->next == NULL)
			&& ptr->type == PIPE)
			return (1);
		if (ptr->type == PIPE && ptr->next
			&& ptr->next->type == PIPE)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

bool	invalid_redirect(t_lexer *token)
{
	t_lexer	*ptr;

	ptr = token;
	while (ptr)
	{
		if ((ptr->type != PIPE && ptr->type != WORD)
			&& (ptr->next == NULL || ptr->next->type != WORD))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}
int ft_return(t_info *data, char *str, int nb)
{
	ft_free(data, NULL);
	ft_khrej(str, nb);
	return(0);
}
int	syntax_error(t_info *data)
{
	t_lexer	*ptr;

	if (invalid_pipe(data->tokens))
		return(ft_return(data, "invalid_pipe", 2));
	if (invalid_redirect(data->tokens))
		return(ft_return(data, "invalid_redirection", 2));
	find_file(data->tokens);
	ptr = data->tokens;
	while (ptr)
	{
		if (ptr->type == FILENAME && (!ptr->last_joind
				|| size_ofdouble(ptr->last_joind) != 1))
			return(ft_return(data, "ambiguous redirect", 1));
		ptr = ptr->next;
	}
	return(1);
}
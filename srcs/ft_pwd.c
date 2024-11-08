/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhatim <rkhatim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:55:07 by rkhatim           #+#    #+#             */
/*   Updated: 2024/11/07 16:05:57 by rkhatim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		printf("%s\n", strerror(errno));
		g_main.exit_status = 1;
			return ;
	}
	printf("%s\n", path);
	g_main.exit_status = 0;
	free(path);
}
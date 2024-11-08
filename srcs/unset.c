/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:06:19 by blackstar         #+#    #+#             */
/*   Updated: 2024/10/27 19:37:27 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    remove_and_switch(int i)
{
    int last;

    last = arr2d_size(g_main.env) - 1;
    if (i < last)
    {
        free(g_main.env[i]);
        g_main.env[i] = my_strdup(g_main.env[last]);
        free(g_main.env[last]);
        g_main.env[last] = NULL;
    }
    else
    {
        free(g_main.env[i]);
        g_main.env[i] = NULL;
    }
}

int len_to_eql(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    return (i);
}

void    find_to_remove(char *str)
{
    int i;
    int len;
    int len1;

    i = -1;
    len = ft_strlen(str);
    while(g_main.env[++i])
    {
        len1 = len_to_eql(g_main.env[i]);
        if (!ft_strncmp(g_main.env[i], str, len)
            && len1 == len)
            remove_and_switch(i);
    }
}

void    unset(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd->arguments[++i])
        find_to_remove(cmd->arguments[i]);
}

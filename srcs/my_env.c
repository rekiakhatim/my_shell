/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 21:25:30 by hboustaj          #+#    #+#             */
/*   Updated: 2024/10/26 12:14:02 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int arr2d_size(char **str)
{
    int i;

    i = 0;
    while(str && str[i])
        i++;
    return(i);
}

void    env_dup(void)
{
    int len;
    
    g_main.env_size = arr2d_size(__environ);
    g_main.env = ft_calloc(g_main.env_size + 1, sizeof(char *));
    len = duplicate_2d(__environ, g_main.env, 0);
    g_main.env[len] = NULL;
}

char *get_env(char *key)
{
    char    **saved;
    char    *returned;

    saved = __environ;
    __environ = g_main.env;
    returned = getenv(key);
    __environ = saved;
    return(returned);
}
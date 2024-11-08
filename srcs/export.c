/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhatim <rkhatim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:13:46 by blackstar         #+#    #+#             */
/*   Updated: 2024/11/06 14:24:57 by rkhatim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_args(t_cmd *cmd)
{
    int nb;
    int i;

    i = 1;
    nb = 0;
    while (cmd->arguments[i])
    {
        if (valide_keyname(cmd->arguments[i]) >= -1)
            nb++;
        else
            return(-1);
        i++;
    }
    return (nb);
}

int    ft_realloc()
{
    char **str;
    int i;

    str = ft_calloc((g_main.env_size * 2) + 1, sizeof(char *));
    g_main.env_size *= 2;
    i = duplicate_2d(g_main.env, str, 0);
    free_double(g_main.env);
    g_main.env = str;
    return (i);
}

void    ft_print()
{
    char *str;
    char *temp;
    int i;

    i = 0;
    while (g_main.env && g_main.env[i])
    {
        str = NULL;
        str = my_strdup("declare -x ");
        temp = key_name(g_main.env[i], valide_keyname(g_main.env[i]));
        str = my_strjoin(str, temp);
        free(temp);
        temp = export_value(g_main.env[i]);
        if(temp)
        {
            str = my_strjoin(str, "\"");
            str = my_strjoin(str, temp);
            str = my_strjoin(str, "\"");
            free(temp);
        }
        printf("%s\n", str);
        i++;
        free(str);
    }
}

void export(t_cmd *cmd)
{
    int len;
    int last;
    int i;

    if(!cmd->arguments[1])
    {
        ft_print();
        return ;
    }
    i = 0;
    while(cmd->arguments[++i])
    {
        if(valide_keyname(cmd->arguments[i]) < -1)
            printf("bash: export: %s: not a valid identifier", cmd->arguments[i]);
        if(valide_keyname(cmd->arguments[i]) < -1)
            continue ;
        find_to_remove(cmd->arguments[i]);
        len = arr2d_size(g_main.env);
        if (len >= g_main.env_size - 1)
            last = ft_realloc();
        else
            last = len;
        g_main.env[last] = my_strdup(cmd->arguments[i]);
        last++;
    }
}

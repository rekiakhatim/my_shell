/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:43:49 by hboustaj          #+#    #+#             */
/*   Updated: 2024/10/30 18:36:37 by blackstar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    update_env(char *pwd, char *newpwd)
{
    int i;
    
    i = -1;
    while(g_main.env[++i])
    {
        if(!ft_strncmp(g_main.env[i], "PWD=", 4))
        {
            free(g_main.env[i]);
            g_main.env[i] = my_strjoin(my_strdup("PWD="), newpwd);
        }
        if(!ft_strncmp(g_main.env[i], "OLDPWD=", 7))
        {
            free(g_main.env[i]);
            g_main.env[i] = my_strjoin(my_strdup("OLDPWD="), pwd);
        }
    }
}

bool    cd(t_cmd *cmd)
{
    char    *pwd;
    char    *newpwd;
    int     reslt;

    pwd = getcwd(NULL, 0);
    reslt = chdir(cmd->arguments[1]);
    if(reslt)
        return (1);
    newpwd = getcwd(NULL, 0);
    update_env(pwd, newpwd);
    free(pwd);// last update
    free(newpwd);// last update
    return(0);
}

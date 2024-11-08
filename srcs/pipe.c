/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhatim <rkhatim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 09:41:00 by rkhatim           #+#    #+#             */
/*   Updated: 2024/11/06 16:11:05 by rkhatim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int handle_pipes(t_cmd *cmd)
{
    if (cmd->pipefd[0] != 0)
    {
        if (dup2(cmd->pipefd[0], STDIN_FILENO) == -1)
        {
            perror("dup2");
            return (-1);
        }
        close(cmd->pipefd[0]);
    }

    if (cmd->pipefd[1] != 0)
    {
        if (dup2(cmd->pipefd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2");
            return (-1);
        }
        close(cmd->pipefd[1]);
    }
    return 0;
}

void waiting(void)
{
    int status;
    int last_status = 0;
 
    while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
            last_status = WEXITSTATUS(status);
    }
    g_main.exit_status = last_status;
}


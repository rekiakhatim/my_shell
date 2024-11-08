// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   execution.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/17 12:27:48 by yuki              #+#    #+#             */
// /*   Updated: 2024/10/31 18:35:40 by hboustaj         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */


#include "minishell.h"


void	child_routine(t_cmd *cmd)
{
    int e;
	//init_signals();
	handle_pipes(cmd);
	handle_redirections(cmd->file);
	e = execute_command(cmd);
	exit(e);
}

void	exec(t_cmd *cmd)
{
	int pipefd[2];
    pid_t pid;

	while (cmd->next)
	{
			pipe(pipefd);
			// protect pipe

			cmd->pipefd[1] = pipefd[1];
			cmd->next->pipefd[0] = pipefd[0];
			cmd->pipefd[2] = pipefd[0];

			pid = fork();
			// protect fork

			if (!pid)
					child_routine(cmd); // it must have exit() at the end of the routine

			if (cmd->pipefd[0])
					close(cmd->pipefd[0]);
			if (cmd->pipefd[1])
					close(cmd->pipefd[1]);

			
			cmd = cmd->next;
	}

	if (cmd->pipefd[0] || !is_builtin(cmd))
	{       
			pid = fork();
			// protect fork

			if (!pid)
					child_routine(cmd); // it must have exit() at the end of the routine

			if (cmd->pipefd[0])
					close(cmd->pipefd[0]);
			if (cmd->pipefd[1])
					close(cmd->pipefd[1]);

			// wait for all the child processes then get the exit status of the last process
			waiting();
	}
	else // builtins only
	{
			//save_stdin_stdout(); dup
			handle_redirections(cmd->file);
			excute_builtin(cmd);
			//recover_stdin_stdout(); dup2 // close 
	}
}

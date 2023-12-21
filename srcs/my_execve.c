/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoudiallo <fatoudiallo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:44:08 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/19 18:38:57 by fatdiall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_redir_parent(int fd[2], int haspipe)
{
	if (haspipe)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

void	do_redir_child(int fd[2], int haspipe, int file_redir)
{
	if (haspipe)
	{
		if (!file_redir)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

int	launch_execve(t_data *datas, char **args, char *prog_path, int haspipe)
{
	pid_t	pid;
	int		fd[2];

	if (haspipe)
		pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		printf("error while forking");
		return (1);
	}
	if (pid == 0)
	{
		do_redir_child(fd, haspipe, datas->file_redir_out);
		execve(prog_path, args, datas->copy_env);
		exit_minishell(datas);
	}
	do_redir_parent(fd, haspipe);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &datas->cmd_ret, 0);
	signal(SIGINT, handlerctrlc);
	return (0);
}

void	get_return_status(t_data *datas)
{
	if (WIFEXITED(datas->cmd_ret))
		datas->exit_status = WEXITSTATUS(datas->cmd_ret);
	else if (WIFSIGNALED(datas->cmd_ret))
		datas->exit_status = WTERMSIG(datas->cmd_ret);
	else if (WIFSTOPPED(datas->cmd_ret))
		datas->exit_status = WSTOPSIG(datas->cmd_ret);
}

int	my_execve(char **args, t_data *datas, int haspipe)
{
	char	*prog_path;

	if (ft_strchr(args[0], '/'))
		prog_path = ft_strdup(args[0]);
	else
		prog_path = search_path(args, datas);
	if (!prog_path)
		return (1);
	launch_execve(datas, args, prog_path, haspipe);
	get_return_status(datas);
	free(prog_path);
	return (0);
}

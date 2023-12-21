/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatdiall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:41:15 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/21 09:41:20 by idumenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_launcher(t_data *datas, int i, int err, int haspipe)
{
	while (datas->args_arr[++i])
	{
		haspipe = 0;
		if (datas->args_arr[i + 1])
		{
			if (datas->args_arr[i + 1][0][0] == '|')
				haspipe = 1;
		}
		err = check_redir(datas->args_arr[i], datas);
		if (err == 1)
			return (1);
		err = look_for_builtin(datas->args_arr[i], datas, haspipe);
		if (err != 0)
			err = my_execve(datas->args_arr[i], datas, haspipe);
		if (err)
			printf("%s: command not found\n", datas->args_arr[i][0]);
		reset_redirs(datas);
		if (haspipe)
			i++;
	}
	return (err);
}

void	main_command_loop(t_data *datas)
{
	int	err;

	while (!datas->exit)
	{
		err = 0;
		make_prompt(datas);
		datas->cmd_line = readline(datas->prompt);
		if (datas->cmd_line == NULL)
			break ;
		if (datas->cmd_line[0] && !is_only_spaces(datas->cmd_line))
		{
			add_history(datas->cmd_line);
			err = parse(datas->cmd_line, datas);
			if (!err)
			{
				err = cmd_launcher(datas, -1, 0, 0);
				clear_data_args_arr(datas);
			}
		}
		free(datas->cmd_line);
		dup2(datas->saved_fd_in, STDIN_FILENO);
		dup2(datas->saved_fd_out, STDOUT_FILENO);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	datas;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handlerctrlc);
	init_vars(env, &datas);
	main_command_loop(&datas);
	exit_minishell(&datas);
	return (0);
}

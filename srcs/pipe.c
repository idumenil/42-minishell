#include "../includes/minishell.h"

int	pipe_handle(char *args, t_data *datas)
{
	int  pipe_fd[2];
    pid_t child_pid;

    if (pipe(child_pid) == -1) {
        perror("Erreur lors de la création du pipe");
        exit(EXIT_FAILURE);
    }
    
    if (child_pid == 0) 
    {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        printf("Processus pere\n");
        //perror("Erreur lors de l'exécution de execve");
        //exit(EXIT_FAILURE);
    }

    else 
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
		printf("Processus fils\n");
        //perror("Erreur lors de l'exécution de execve");
        //exit(EXIT_FAILURE);
    }
}

int	check_pipe(char **cmd_line, t_data *datas)
{
	int	i;

	i = 0;
	while (cmd_line[i] != NULL)
	{
		if (ft_strcmp(cmd_line[i], "|") == 0)
		{
			if (!(cmd_line[i + 1]))
			{
				printf("syntax error near unexpected token `newline'\n");
				return (1);
			}
			else
			{
				pipe_handle(cmd_line[i + 1], datas);
				free(cmd_line[i + 1]);
			}
			free(cmd_line[i]);
			cmd_line[i] = NULL;
			i++;
		}
		i++;
	}
	return (0);
}

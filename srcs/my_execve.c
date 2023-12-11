
#include "../includes/minishell.h"

char	*search_path(char **args, t_data *datas)
{
	int		i;
	char *path;
	char **paths_in_array;
	char *path_found;

	i = 0;
	path = get_env_var("PATH", datas->orig_env);
	if (!path)
		return (NULL);
	paths_in_array = ft_split(path, ':');
	while (paths_in_array[i])
	{
		path_found = ft_strjoin_with_slash(paths_in_array[i], args[0]);
		if (access(path_found, F_OK) == 0)
		{
			free_2d_char(paths_in_array);
			return (path_found);
		}
		free(path_found);
		i++;
	}
	free_2d_char(paths_in_array);
	return (NULL);
}

int	my_execve(char **args, t_data *datas)
{
	pid_t	pid;
	char	*prog_path;

	if (ft_strchr(args[0], '/'))
		prog_path = ft_strdup(args[0]);
	else
		prog_path = search_path(args, datas);
	// if (prog_path)
	// 	printf("Found %s at %s\n\n", args[0], prog_path);
	if (!prog_path)
		return(1);
	pid = fork();
	if (pid == -1)
	{
		printf("error while forking");
		return (1);
	}
	else if (pid == 0)
		execve(prog_path, args, NULL);
	else
	{
		//int status;
		//wait(&status);

		datas->cmd_ret = waitpid(pid, &datas->cmd_ret, 0);
        datas->exit_status = WEXITSTATUS(datas->cmd_ret);
        printf("%d\n", datas->exit_status); //debug

		if (WIFEXITED(datas->exit_status))
            printf("Le processus fils s'est terminé normalement avec le code de sortie : %d\n", WEXITSTATUS(datas->exit_status));
		else if (WIFSIGNALED(datas->exit_status)) 
            printf("Le processus fils s'est terminé à cause du signal : %d\n", WTERMSIG(datas->exit_status));
        
	}
	free(prog_path);
	return (0);
}

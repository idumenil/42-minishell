#include "../includes/minishell.h"

// t_data g_data;


void	name_is_valid(char **args)
{
	// carctères autorisés
}

void my_export(char **args)
{
	int	name_len;
	const char *equal;
	char	*var_name;
	char 	**temp_env;
	int		line;

	equal = ft_strchr(args[1], '=');
	name_len = equal - args[1];
	var_name = ft_strldup(args[1], name_len);
	line = get_env_var_line(var_name, g_data.copy_env);
	if (line >= 0)
	{
		free(g_data.copy_env[line]);
		g_data.copy_env[line] = ft_strdup(args[1]);
	}
	else
	{
		temp_env = copy_env_var(g_data.copy_env);
		free_2d_char(g_data.copy_env);
		temp_env[nb_lines_arr(temp_env)] = ft_strdup(args[1]);
		g_data.copy_env = temp_env;
	}
}

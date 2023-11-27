#include "../includes/minishell.h"

#include <stdbool.h>

#define BUF_CMD_LINE 1024

//fonctions utils pour safe malloc
void	*safe_malloc(size_t bytes)
{
	void	*res;
	
	res = malloc(bytes);
	if (!res)
		return (NULL);
	return (res);
}

// Fonction pour allouer et initialiser le tableau de tokens
// TO DO (optional) affiner l'allocation mémoire, remplacer BUF_CMD_LINE par la taille exacte de la commande
char **init_tokens_table()
{
    char **args;
    
    args = safe_malloc(sizeof(char *) * BUF_CMD_LINE);
    args[0] = safe_malloc(sizeof(char) * (BUF_CMD_LINE + 1));
    
    if (!args[0])
    {
        free(args);
        return NULL;
    }

    return args;
}

// Fonction pour parser la ligne de commande en tokens
// TO DO : diviser en deux sous-fonctions pour la norme
char **tokenise(char *cmd_line) 
{
    char **args;
    bool is_quote;
    int token_id, carac_nb, i;
    
    args = init_tokens_table(sizeof(char *) * BUF_CMD_LINE);
    token_id = 0;
    carac_nb = 0;
    i = 0;
    is_quote = false;
    while (cmd_line[i]) 
    {
        if (cmd_line[i] == '\'' || cmd_line[i] == '\"')
            is_quote = !is_quote;
        else if (isspace(cmd_line[i]) && !is_quote) 
        {
            args[token_id][carac_nb] = '\0';
            carac_nb = 0;
            token_id++;
            args[token_id] = safe_malloc(sizeof(char) * (BUF_CMD_LINE + 1));
        }
        else
            args[token_id][carac_nb++] = cmd_line[i];
        i++;
    }
    args[token_id][carac_nb] = '\0';
    args[token_id + 1] = NULL;
    if (args[0][0] == '\0') {
        free(args[0]);
        args[0] = NULL;
    }
    return args;
}

char **parse(char *cmd_line)
{
	tokenise(cmd_line);
	//to do : syntax analysis
}


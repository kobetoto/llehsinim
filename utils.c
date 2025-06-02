#include "../includes/main.h"

int     ft_error(char *msg, int code)
{
	perror(msg); // affiche automatiquement le message d'erreur lié à errno
	return (code);
}

int     ft_put_error(char *msg, int code)
{
	write(2, "minishell: ", 11);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (code);
}

void    ft_clear_tokens(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = tmp;
    }
}

t_token *ft_new_token(char *value)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (new == NULL)
    {
        ft_error("malloc ERR", 3);
        return (NULL);
    }
    new->value = ft_strdup(value);
    new->type = 0;
    new->next = NULL;
    return (new);
}

void	ft_token_add_back(t_token **lst, t_token *new_t)
{
    t_token *tmp;

    tmp = NULL;
    if ((lst == NULL) || (new_t == NULL))
        return;
    if(*lst == NULL)
        {
            *lst = new_t;
            return;
        }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_t;
}
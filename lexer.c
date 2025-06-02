#include "../includes/main.h"

void    ft_assignation(t_token *lst)
{
    while (lst)
    {
        if( ft_strcmp(lst->value, "<")  == 0)
            lst->type = T_REDIRECT_IN;
        else if(  ft_strcmp(lst->value, ">")  == 0)
            lst->type = T_REDIRECT_OUT;
        else if(  ft_strcmp(lst->value, ">>")  == 0)
            lst->type = T_APPEND;
        else if(  ft_strcmp(lst->value, "<<")  == 0)
            lst->type = T_HEREDOC;
        else
            lst->type = T_WORD; 
        lst = lst->next;
    }
}

t_token *ft_tokenise(char **arr)
{
    int         i;
    t_token     *tokens;
    t_token     *new;

    i = 0;
    tokens = NULL;
    while (arr[i])
    {
        new = ft_new_token(arr[i]);
        if (new == NULL)
            {
                ft_clear_tokens(tokens);
                return (NULL);
            }
        ft_token_add_back(&tokens, new);
        i++;
    }
    return (tokens);
}

t_token *ft_lexer(char *line)
{
    t_token *token_lst;
    char    **tmp;

    token_lst = NULL;
    tmp = ft_split(line, ' ');
    if (tmp == NULL)
        {
            ft_free_split(tmp);
            ft_put_error("FT_SPLIT ERR (LEXER)", 1);
            return (NULL);
        }
    token_lst = ft_tokenise(tmp);
    ft_free_split(tmp);
    ft_assignation(token_lst);
    return (token_lst);
}

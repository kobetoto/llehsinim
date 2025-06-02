#include "../includes/main.h"

int main(int ac, char **av, char **envp)
{
    (void) ac;
    (void) av;
    (void) envp;
    char    *line = NULL;
    t_token *lst = NULL;
    int i = 0;

    while(1)
    {
        line = readline("bash$ ");
        if (line == NULL)
            break;
		if (*line)
			add_history(line);
        i = 0;
        lst = ft_lexer(line);
        while (lst)
        {
            i++;
            printf("node'%i'\n%s => %i\n\n",i ,lst->value, lst->type);
            lst = lst->next;
        }
        free(line);
    }
    return (0);
}
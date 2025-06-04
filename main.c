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


//main ->dev
int minishell(int ac, char **av, char **env)
{
	char *line;
	char *test_expand;
	t_list *lst;
	t_list *envp_lst;
	t_cmd *cmd;
	int i;

	(void)ac;
	(void)av;
	lst = NULL;
	line = NULL;
	envp_lst = ft_envp_lst(env);
	while (1)
	{
		line = readline("Minishell$ ");
		if (line == NULL)
			break;
		if (*line)
			add_history(line);
		if (ft_check_err(line) == 1)
			ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		if (ft_check_err(line) == 2)
			ft_putendl_fd("minishell: syntax error near unexpected token `&'", 2);
		ft_builtin(line, &envp_lst);
		test_expand = ft_expand_variable(line, &envp_lst);
		if (test_expand != NULL)
			printf("%s\n", test_expand);
		ft_export_var(line, &envp_lst);
		// exec_cmd(line, &envp_lst);
		// if (!parse_input_line(line, &lst))
		// {
		// 	printf("Erreur: parsing des commandes échoué\n");
		// 	free(line);
		// 	free_list(lst);
		// 	lst = NULL;
		// 	continue ;
		// }
		lst = parse_input_line(line, &lst);
		while (lst)
		{
			cmd = (t_cmd *)lst->content;
			printf("\n\nNEW NODE\n\n");
			i = 0;
			while (cmd->cmd[i])
			{
				if (ft_strcmp(*cmd->cmd, "<") == 0)
					cmd->redirect->redirect = (t_redirection_type) REDIR_STDIN;
				else if (ft_strcmp(*cmd->cmd, ">") == 0)
					cmd->redirect->redirect = (t_redirection_type) REDIR_STDOUT;
				else if (ft_strcmp(*cmd->cmd, ">>") == 0)
					cmd->redirect->redirect = (t_redirection_type) REDIR_APPEND;
				else if (ft_strcmp(*cmd->cmd, "<<") == 0)
					cmd->redirect->redirect = (t_redirection_type) REDIR_HEREDOC;
				else
				{
					cmd->redirect_in = NO_REDIR;
					cmd->redirect_out = NO_REDIR;
					
				}
				printf("==%s==\n", cmd->cmd[i]);
				printf("==%i==\n", cmd->redirect->redirect);
				i++;
			}
			lst = lst->next;
		}
		free_list(lst);
		lst = NULL;
		free(line);
	}
	return 1;
}

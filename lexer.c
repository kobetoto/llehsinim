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



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:16:41 by rcini-ha          #+#    #+#             */
/*   Updated: 2025/06/04 12:16:30 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_command_list(t_list *cmd_list)
{
	t_cmd	*cmd;
	int		i;
	int		cmd_index;

	cmd_index = 0;
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		printf("📦 Command #%d:\n", cmd_index);
		if (cmd && cmd->cmd)
		{
			i = 0;
			while (cmd->cmd[i])
			{
				printf("  argv[%d] = %s\n", i, cmd->cmd[i]);
				i++;
			}
		}
		else
			printf("  (empty command)\n");
		cmd_list = cmd_list->next;
		cmd_index++;
	}
}

t_list	*add_node(char **split_command, t_list **cmd_list)
{
	t_cmd	*cmd_struct;
	t_list	*new_node;

	cmd_struct = malloc(sizeof(t_cmd));
	if (!cmd_struct)
		return (NULL);
	cmd_struct->cmd = split_command;
	new_node = ft_lstnew(cmd_struct);
	if (!new_node)
	{
		free(cmd_struct);
		return (NULL);
	}
	ft_lstadd_back(cmd_list, new_node);
	return (new_node);
}
//#todo
int	create_command_node(char *command_str, t_list **cmd_list)
{
	char	**split_command;
	t_list	*lst;

	lst = NULL;
	// TODO: lexer/tokenisation (redir, etc.)
	split_command = ft_split(command_str, ' ');
	if (!split_command)
		return (0);
	lst = add_node(split_command, cmd_list);
	if (!lst)
		return (0);
	return (1);
}

char	*get_completed_line(char *line, char quote)
{
	char	*new_line;
	char	*addition;

	new_line = ft_strdup(line);
	if (!new_line || (quote != '\'' && quote != '\"'))
		return (NULL);
	while (1)
	{
		if (!check_unclosed_quotes(new_line))
			break ;
		write(1, ">", 2);
		addition = get_next_line(STDIN_FILENO, '\n');
		if (!addition)
			break ;
		new_line = ft_strjoin(new_line, "\n", 1, 0);
		if (!new_line)
			return (NULL);
		new_line = ft_strjoin(new_line, addition, 1, 1);
		if (!new_line)
			return (NULL);
	}
	return (new_line);
}
char	*process_quotes(char *str)
{
	int	quotes_is_valide;

	quotes_is_valide = check_unclosed_quotes(str);
	if (quotes_is_valide == UNCLOSED_SINGLE_QUOTE)
		return (get_completed_line(str, '\''));
	else if (quotes_is_valide == UNCLOSED_DOUBLE_QUOTE)
		return (get_completed_line(str, '\"'));
	else
		return (ft_strdup(str));
}
t_list	*parse_input_line(char *line, t_list **cmd_list)
{
	char	**commands;
	int		i;
	t_list	*last_nodes;
	char	*new_line;

	last_nodes = NULL;
	new_line = process_quotes(line);
	commands = split_smart_pipe(new_line);
	if (!commands)
		return (free(new_line), (NULL));

	//#todo  parcourire lise chaine et gere les "||" "&" et vide OK ft_check_err () au debut du programme
	//#todo  utiliser fonction qui utilise une fonction sur un elememt dune lst
	i = 0;
	while (commands[i])
	{
		if (!create_command_node(commands[i], cmd_list))
			return (free_list(*cmd_list), free(new_line),
				free_commands(commands), (NULL));
		i++;
	}
	print_command_list(*cmd_list);
	free_commands(commands);
	free(new_line);
	return ((*cmd_list));
}


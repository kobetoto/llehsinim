/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:16:41 by rcini-ha          #+#    #+#             */
/*   Updated: 2025/05/20 12:08:15 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// int	is_redirect(char c)
// {
// 	int			i;
// 	const char	redir[] = {NULL, ">", "<", "<<", ">>"};

// 	i = 0;
// 	while (redir[i])
// 	{
// 		if (c == redir[i])
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
// char	*redirect_space(char *cmd)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[j] != ' ' && !is_redirect(cmd[j])
// 			&& cmd[i] == is_redirect(cmd[i]))
// 		{
// 		}
// 		j = i;
// 		i++;
// 	}
// 	return (cmd);
// }

void	free_commands(char **commands)
{
	int	i;

	i = 0;
	if (!commands)
		return ;
	while (commands[i])
	{
		free(commands[i]);
		i++;
	}
	free(commands);
}
void	free_list(t_list *cmd_list)
{
	t_list	*temp;
	t_cmd	*cmd;

	while (cmd_list)
	{
		temp = cmd_list;
		cmd = (t_cmd *)cmd_list->content;
		if (cmd)
		{
			free_commands(cmd->cmd);
			free(cmd);
		}
		cmd_list = cmd_list->next;
		free(temp);
	}
}

int	add_command_node(char *command_str, t_list **cmd_list)
{
	t_cmd	*cmd_struct;
	char	**split_command;
	t_list	*new_node;

	cmd_struct = malloc(sizeof(t_cmd));
	if (!cmd_struct)
		return (0);
	split_command = ft_split(command_str, ' ');
	if (!split_command)
		return (free(cmd_struct), 0);
	cmd_struct->cmd = split_command;
	new_node = ft_lstnew(cmd_struct);

	if (!new_node)
		return (free(split_command), free(cmd_struct), (0));
	ft_lstadd_back(cmd_list, new_node);
	return (1);
}

void	print_list(t_list *cmd_list)
{
	t_cmd	*cmd;

	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		if (cmd && cmd->cmd && cmd->cmd[0])
			printf("Commande : %s\n", cmd->cmd[0]);
		else
			printf("Commande vide ou non initialisée\n");
		cmd_list = cmd_list->next;
	}
	printf("Fin de la liste\n");
}

t_list	*parse_commands(char *line, t_list **cmd_list)
{
	char	**commands;
	int		i;
	t_list	*last_nodes;

	last_nodes = NULL;
	commands = ft_split(line, '|');
	if (!commands)
		return (NULL);
	i = 0;
	while (commands[i])
	{
		if (!add_command_node(commands[i], cmd_list))
			return (free_list(*cmd_list), free_commands(commands), (NULL));
		i++;
	}
	free_commands(commands);
	return ((*cmd_list));
}

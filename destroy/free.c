/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:46:06 by rcini-ha          #+#    #+#             */
/*   Updated: 2025/06/02 13:46:20 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

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

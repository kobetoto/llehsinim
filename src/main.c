/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:36:48 by rcini-ha          #+#    #+#             */
/*   Updated: 2025/05/21 09:25:19 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_list	*lst;
	t_list	*envp_lst;

	(void) ac;
	(void) av;
	lst = NULL;
	line = NULL;
	envp_lst = ft_envp_lst(envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		line = readline("Minishell$ ");
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		ft_builtin(line, &envp_lst);
		if (!parse_commands(line, &lst))
		{
			printf("Erreur: parsing des commandes échoué\n");
			free(line);
			free_list(lst);
			lst = NULL;
			continue ;
		}
		// print_list(lst);
		free_list(lst);
		lst = NULL;
		free(line);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:36:48 by rcini-ha          #+#    #+#             */
/*   Updated: 2025/05/27 13:30:48 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	*test_expand;
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
		test_expand = ft_expand_variable(line, &envp_lst);
		if (test_expand != NULL)
			printf("%s\n", test_expand);
		ft_export_var(line, &envp_lst);
		exec_cmd(line, &envp_lst);//en cours.............
		// if (!parse_commands(line, &lst))
		// {
		// 	printf("Erreur: parsing des commandes échoué\n");
		// 	free(line);
		// 	free_list(lst);
		// 	lst = NULL;
		// 	continue ;
		// }
		print_list(lst);
		free_list(lst);
		lst = NULL;
		free(line);
	}
	return (0);
}

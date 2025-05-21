/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:20:46 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/21 15:59:30 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

char *ft_get_env(char *key, t_list	*envp_lst)
{
    int len;
    char *env_var;

    len = ft_strlen(key);
    env_var = NULL;
    while(envp_lst)
    {
        env_var = envp_lst->content;
        if(ft_strncmp(env_var, key, len) == 0 && env_var[len] == '=')
            return (env_var +len +1);
        envp_lst = envp_lst->next;
    }
    return (0);
}
/*
    split line pour les faire passer aux fonctions!
    env doit avoir une ligne avec env et sans alpha num apres
    pwd doit pouvoit sexecuter avec peut importe ce quil ya derriere
    echo gerer les cas speciaux ' '' $env $toto $tata

*/


void ft_builtin(char *line, t_list **envp_lst)
{
    char    **line_split;
    t_list  *envp_lst_cpy;

    envp_lst_cpy = *envp_lst;
    
    line_split = ft_split(line, " ");
    if (line_split = NULL)
        return;
    if (ft_strncmp(line, "cd", 2) == 0)
        ft_cd(envp_lst, line);
    if (ft_strncmp(line, "pwd ", 4) == 0)
        printf("%s\n", ft_get_env("PWD", envp_lst_cpy));
    if (ft_strncmp(line, "env", 3) == 0)
        ft_print_env(envp_lst_cpy);
    if (ft_strncmp(line, "echo ", 5) == 0)
        ft_echo(line);
}

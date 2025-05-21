/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:29:50 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/21 15:15:21 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

t_list  *ft_envp_lst(char **envp)
{    
    t_list  *head_envp_lst;
    int i;

    head_envp_lst = NULL;
    i = 0;
    while(envp[i])
    {
        t_list *new_node = malloc(sizeof(t_list));
        new_node->content = ft_strdup(envp[i]);
        if(new_node->content == NULL)
            ft_putendl_fd("new node malloc err",2);
        ft_lstadd_back(&head_envp_lst, new_node);
        i++;
    }
    return (head_envp_lst);
}

char **ft_envp_copy(char **envp)
{
    char **envp_cpy;
    int var_count;
    int i;
    int j;

    i = 0;
    j = 0;
    var_count = 0;
    while (envp[var_count])
        var_count++;
    envp_cpy = malloc(sizeof(char *) * (var_count + 1));
    if (envp_cpy == NULL)
        printf("==ERR== malloc envp_cpy\n");
    while (envp[i])
    {
        envp_cpy[i] = ft_strdup(envp[i]);
        /*
        En cas d’échec d’allocation d’un élément,
        tu pourrais libérer tous les éléments déjà alloués
        (envp_cpy[0] à envp_cpy[i - 1])
        pour éviter les memory leaks (fuite mémoire).
        POSSIBLE DE LE METTRE CETTE FUNCTION DANS UNE AUTRE FONCTION
        */
        if (envp_cpy[i] == NULL)
        {
            while (j < i)
            {
                free(envp_cpy[j]);
                j++;
            }
            free(envp_cpy);
            printf("==ERR== envp_cpy dup\n");
        }
        i++;
    }
    envp_cpy[i] = NULL;
    return (envp_cpy);
}

void    ft_print_env(t_list *envp)
{
    while (envp)
    {
        printf("%s\n", (char *)envp->content);
        envp = envp->next;
    }
}
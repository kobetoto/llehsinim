/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:58:24 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/21 09:58:55 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

void ft_export(t_list **envp_lst, char *key, char *value)
{
    t_list  *cur;
    int key_len;
    char *new_line;
    char *full_line;
    char *env_var;
    t_list *new_node;
    
    cur = *envp_lst;
    key_len = ft_strlen(key);
    new_node = NULL;
    while (cur)
    {
        env_var = cur->content;
        if (ft_strncmp(env_var, key, key_len) == 0 && env_var[key_len] == '=')
        {
            free(cur->content);
            new_line = ft_strjoin(key, "=", 0 ,0);
            full_line = ft_strjoin(new_line, value, 0 ,0);
            cur->content = full_line;
            return;
        }
        cur = cur->next;
    }
    new_line = ft_strjoin(key, "=", 0, 0);
    full_line = ft_strjoin(new_line, value, 1, 0);
    new_node = malloc(sizeof(t_list));
    if (!new_node)
        return ;
    new_node->content = full_line;
    new_node->next = NULL;
    new_node->prev = NULL;
    ft_lstadd_back(envp_lst, new_node);
}
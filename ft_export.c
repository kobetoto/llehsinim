/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:58:24 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/26 16:47:00 by thodavid         ###   ########.fr       */
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
    ft_lstadd_back(envp_lst, new_node);
}

char *ft_expand_variable(char *line, t_list **env)
{
    t_list  *cur;
    char    *key;
    char    **tab;
    int     len;

    cur = *env;
    key = NULL;
    tab = ft_split(line, ' ');
    if (tab == NULL)
    {
        ft_free_split(tab);
        return (NULL);
    }
    if (tab[0][0] != '$')
        return (NULL);
    len = ft_strlen(tab[0]);
    while (cur)
    {
        key = ft_get_key((char *)cur->content);
        if(ft_strcmp(key, tab[0]+1) == 0)
                return (ft_get_value((char *)cur->content));
        cur = cur->next;
    }
    return (NULL);
}

char     *ft_get_value(char *s)
{
    char    *tmp;
    char    *key;
    
    tmp = NULL;
    key = NULL;
    tmp = ft_strchr(s, '=');
    key = ft_strtrim(tmp, "=");
    return (key);
}

char     *ft_get_key(char *s)
{
    int     len;
    int        i;
    char    *key;
    
    len = 0;
    i = 0;
    key = NULL;
    while(s[len] != '=')
        len++;
    key = malloc(sizeof(char) * len +1);
    while(i < len)
    {
        key[i] = s[i];
        i++;
    }
    key[i] = '\0'; 
    return (key);
}


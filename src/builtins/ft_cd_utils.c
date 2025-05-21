/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:25:11 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/21 13:30:33 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

int ft_only_space(char *s)
{
    int i;

    i = 0;
    if (s == NULL)
        return (0);
    while (s[i])
    {
        if (s[i] != ' ' && s[i] != '\t')
            return (0);
        i++;
    }
    return (1);
}

char *ft_create_path(char *pwd, char *dst)
{
    char *path;
    char *tmp;

    path = NULL;
    tmp = NULL;
    if (pwd == NULL || dst == NULL)
        return NULL;
    tmp = ft_strjoin(pwd, "/", 0, 0);
    path = ft_strjoin(tmp, dst, 1, 0);
    return (path);
}

int ft_special_case(char **cmd)
{
    int i;

    i = 0;
    if (cmd == NULL)
        return (0);
    while (cmd[i])
    {
        if (ft_only_space(cmd[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

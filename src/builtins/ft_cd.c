/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:55:07 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/21 14:12:16 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

int ft_cd_home(char **cmd)
{
    int len;

    len = 0;
    while (cmd[len])
        len++;
    if ((len == 1 && ft_strcmp(cmd[0], "cd") == 0))
        return (1);
    if (len > 2 && ft_special_case(cmd) == 0)
        return (0);
    return (0);
}

int ft_cd(t_list **envp_lst, char *line)
{
    char **cmd;
    char *pwd;
    char *home;
    char *path;
    char *old;
    char *new;

    pwd = ft_get_env("PWD", *envp_lst);
    cmd = ft_split(line, ' ');
    if (cmd == NULL)
        return (1);
    if (ft_cd_home(cmd) == 1)
    {
        home = ft_get_env("HOME", *envp_lst);
        if (home == NULL)
        {
            ft_putendl_fd("minishell: cd: Home not set", 2);
            ft_free_split(cmd);
            return (1);
        }
        path = ft_strdup(home);
        if (!path)
        {
            ft_putendl_fd("minishell: cd: malloc error", 2);
            ft_free_split(cmd);
            return (1);
        }
    }
    else if (cmd[1])
        path = ft_create_path(pwd, cmd[1]);
    else
    {
        ft_putendl_fd("minishell: cd: path error", 2);
        ft_free_split(cmd);
        return (1);
    }
    if (!path || access(path, R_OK) != 0 || access(path, X_OK) != 0)
    {
        if (cmd[1])
            printf("minishell: cd: %s: no such file or directory\n", cmd[1]);
        ft_free_split(cmd);
        free(path);
        return (1);
    }
    if (chdir(path) == 0)
    {
        old = getcwd(NULL, 0);
        new = getcwd(NULL, 0);
        ft_export(envp_lst, "OLDPWD", old);
        ft_export(envp_lst, "PWD", new);
        free(old);
        free(new);
    }
    else
        perror("minishell: cd");
    ft_free_split(cmd);
    free(path);
    return (0);
}

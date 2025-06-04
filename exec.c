/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:37:13 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/30 09:40:47 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

int exec_cmd(char *line, char **envp)
{
    char            **tab;
    char            *path;
    char            *key;
    t_cmd           cmd;
    pid_t           pid;
    int               i;
    
    i = 0;
    path = NULL;
    key = NULL;
    tab = ft_split(line, ' ');
    if (tab == NULL)
    {
        ft_free_split(tab);
        return (0);
    }
    cmd.cmd = tab;
    while (envp[i])
    {
        key = ft_get_key(envp[i]);
        if (ft_strcmp("PATH", key) == 0)
        {
            path = ft_get_value(envp[i]);
            break;
        }
        i++;
    }

    printf("path is ==%s==\n",path);
    pid = fork();
    if (pid < 0)
        ft_putendl_fd("Fork err", 2);
        
    else if (pid == 0)
    {
        printf("==I AM THE CHILD PROCESS REMPLACE BY THE EXECVE==\n\n");
        /*****la je lance la fonction****/
    /*
    --->int execve(const char *pathname, char *const argv[], char *const envp[])

    --->argv is an array of pointers to strings passed to the new program as its command-line arguments.  
                By  convention,  the  first  of these strings (i.e., argv[0]) should contain the filename associated with the file being executed.

    --->envp is an array of pointers to strings, conventionally of the form key=value, which are passed as the  environment  of  the  new program.  
                The envp array must be terminated by a NULL pointer.
    
    */
    execve(path, tab, envp);
    perror("execve failed");
    exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
        printf("==....I AM THE PARENT AND WAIT MY CHILD PROCESS FINISH......==\n\n");
    }
    return (1);
}
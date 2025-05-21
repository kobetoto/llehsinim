/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:35:24 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/21 15:50:02 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

ft_echo_parse(char **tab)
{
    while
}

void    ft_echo(char *line)
{
    char    **tab;
    
    tab = ft_split(line, " ");
    if (tab == NULL)
        return;
    ft_echo_pars(tab);
}



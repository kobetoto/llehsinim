/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:22:15 by rcini-ha          #+#    #+#             */
/*   Updated: 2025/05/14 13:22:25 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		g_last_status = 0;

void	handle_sigint(int a)
{
	(void)a;
	g_last_status = 130;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_heredoc(int a)
{
	(void)a;
	g_last_status = 130;
	ft_printf("\n");
	close(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:35:46 by rcini-ha          #+#    #+#             */
/*   Updated: 2025/06/04 16:34:10 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_redirection_type
{
	NO_REDIR,
	REDIR_STDIN,
	REDIR_STDOUT,
	REDIR_HEREDOC,
	REDIR_APPEND
}					t_redirection_type;




typedef struct s_redirect
{
	char		*name_file;
	t_redirection_type redirect;

}				t_redirect;

typedef struct s_cmd
{
	char		**cmd;
	int			redirect_in;
	int			redirect_out;
	t_redirect	*redirect;

}				t_cmd;

#endif


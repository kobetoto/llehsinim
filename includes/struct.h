/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:35:46 by rcini-ha          #+#    #+#             */
/*   Updated: 2025/05/18 14:16:49 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_redirect
{
	char		*name_file;
	t_redirection_type redirect;

}				t_redirect;
typedef struct s_cmd
{
	char		**cmd;
	int			*redirect_in;
	int			redirect_out;
	t_redirect	*redirect;

}				t_cmd;



#endif

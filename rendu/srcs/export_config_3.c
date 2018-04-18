/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_config_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaspard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 18:47:34 by agaspard          #+#    #+#             */
/*   Updated: 2018/03/06 18:51:20 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		write_hyper(t_env *e, int fd, int i)
{
	char	*tmp;

	while (++i < e->nb_forms)
		if (e->s->forms[i]->form_id == 7)
		{
			ft_putstr_fd("hyperboloid=[", fd);
			tmp = ft_itoa(e->s->forms[i]->pos.x);
			ft_putstr_fd(tmp, fd);
			free(tmp);
			free_write(e->s->forms[i]->pos.y, fd, 1);
			free_write(e->s->forms[i]->pos.z, fd, 1);
			free_write(e->s->forms[i]->norm.x, fd, 1);
			free_write(e->s->forms[i]->norm.y, fd, 1);
			free_write(e->s->forms[i]->norm.z, fd, 1);
			free_write(e->s->forms[i]->rad, fd, 1);
			free_write(e->s->forms[i]->col.r, fd, 1);
			free_write(e->s->forms[i]->col.g, fd, 1);
			free_write(e->s->forms[i]->col.b, 0, 1);
			ft_putendl_fd("]", fd);
		}
}

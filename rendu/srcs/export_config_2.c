/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_config_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlajovec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 17:13:54 by jlajovec          #+#    #+#             */
/*   Updated: 2018/03/06 16:59:43 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		free_write(float new, int fd, int type)
{
	char	*tmp;
	char	*tmpret;

	tmpret = NULL;
	tmp = NULL;
	if (fd == 0)
		ft_putstr_fd(", ", fd);
	if (type == 0)
	{
		tmpret = ft_itoa((int)new);
		ft_putstr_fd(tmpret, fd);
		free(tmpret);
	}
	else if (type == 1)
	{
		tmp = ft_ftoa(new);
		tmpret = ft_strcat(tmp, "\0");
		ft_putstr_fd(tmpret, fd);
		free(tmp);
	}
}

void		write_normal_light(t_env *e, int fd, int i, char *tmp)
{
	if (e->s->forms[i]->form_id == LIGHT)
	{
		ft_putstr_fd("light=[", fd);
		tmp = ft_itoa(e->s->forms[i]->pos.x);
		ft_putstr_fd(tmp, fd);
		free(tmp);
		free_write(e->s->forms[i]->pos.y, fd, 1);
		free_write(e->s->forms[i]->pos.z, fd, 1);
		free_write(e->s->forms[i]->norm.x, fd, 1);
		free_write(e->s->forms[i]->norm.y, fd, 1);
		free_write(e->s->forms[i]->norm.z, fd, 1);
		free_write(e->s->forms[i]->col.r, fd, 1);
		free_write(e->s->forms[i]->col.g, fd, 1);
		free_write(e->s->forms[i]->col.b, 0, 1);
		ft_putendl_fd("]", fd);
	}
}

void		write_lights(t_env *e, int fd, int i)
{
	char	*tmp;

	while (++i < e->nb_forms)
	{
		if (i == 0)
		{
			ft_putstr_fd("ambient_light=[", fd);
			tmp = ft_itoa(e->s->forms[i]->pos.x);
			ft_putstr_fd(tmp, fd);
			free(tmp);
			free_write(e->s->forms[i]->pos.y, fd, 1);
			free_write(e->s->forms[i]->pos.z, fd, 1);
			free_write(e->s->forms[i]->norm.x, fd, 1);
			free_write(e->s->forms[i]->norm.y, fd, 1);
			free_write(e->s->forms[i]->norm.z, fd, 1);
			free_write(e->s->forms[i]->col.r, fd, 1);
			free_write(e->s->forms[i]->col.g, fd, 1);
			free_write(e->s->forms[i]->col.b, 0, 1);
			ft_putendl_fd("]", fd);
		}
		else
			write_normal_light(e, fd, i, tmp);
	}
}

void		write_co_cy(t_env *e, int fd, int i)
{
	char	*tmp;

	while (++i < e->nb_forms)
		if (e->s->forms[i]->form_id == 3 || e->s->forms[i]->form_id == 4)
		{
			if (e->s->forms[i]->form_id == CONE)
				ft_putstr_fd("cone=[", fd);
			else if (e->s->forms[i]->form_id == CYLINDER)
				ft_putstr_fd("cylinder=[", fd);
			tmp = ft_itoa(e->s->forms[i]->pos.x);
			ft_putstr_fd(tmp, fd);
			free(tmp);
			free_write(e->s->forms[i]->pos.y, fd, 1);
			free_write(e->s->forms[i]->pos.z, fd, 1);
			free_write(e->s->forms[i]->norm.x, fd, 1);
			free_write(e->s->forms[i]->norm.y, fd, 1);
			free_write(e->s->forms[i]->norm.z, fd, 1);
			free_write(e->s->forms[i]->rad, fd, 1);
			free_write(e->s->forms[i]->high, fd, 1);
			free_write(e->s->forms[i]->col.r, fd, 1);
			free_write(e->s->forms[i]->col.g, fd, 1);
			free_write(e->s->forms[i]->col.b, 0, 1);
			ft_putendl_fd("]", fd);
		}
}

void		write_planes(t_env *e, int fd, int i)
{
	char	*tmp;

	while (++i < e->nb_forms)
	{
		if (e->s->forms[i]->form_id == PLANE)
		{
			ft_putstr_fd("plane=[", fd);
			tmp = ft_itoa(e->s->forms[i]->pos.x);
			ft_putstr_fd(tmp, fd);
			free(tmp);
			free_write(e->s->forms[i]->pos.y, fd, 1);
			free_write(e->s->forms[i]->pos.z, fd, 1);
			free_write(e->s->forms[i]->norm.x, fd, 1);
			free_write(e->s->forms[i]->norm.y, fd, 1);
			free_write(e->s->forms[i]->norm.z, fd, 1);
			free_write(e->s->forms[i]->col.r, fd, 1);
			free_write(e->s->forms[i]->col.g, fd, 1);
			free_write(e->s->forms[i]->col.b, 0, 1);
			ft_putendl_fd("]", fd);
		}
	}
}

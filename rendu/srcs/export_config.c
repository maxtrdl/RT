/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlajovec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:58:38 by jlajovec          #+#    #+#             */
/*   Updated: 2018/03/06 18:51:06 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

void		write_spheres(t_env *e, int fd, int i)
{
	char	*tmp;

	while (++i < e->nb_forms)
	{
		if (e->s->forms[i]->form_id == SPHERE)
		{
			ft_putstr_fd("sphere=[", fd);
			tmp = ft_itoa(e->s->forms[i]->pos.x);
			ft_putstr_fd(tmp, fd);
			free(tmp);
			free_write(e->s->forms[i]->pos.y, fd, 0);
			free_write(e->s->forms[i]->pos.z, fd, 0);
			free_write(e->s->forms[i]->rad, fd, 0);
			free_write(e->s->forms[i]->col.r, fd, 1);
			free_write(e->s->forms[i]->col.g, fd, 1);
			free_write(e->s->forms[i]->col.b, 0, 1);
			ft_putendl_fd("]", fd);
		}
	}
}

void		write_win_set(t_env *e, int fd)
{
	char	*tmp;

	ft_putstr_fd("intensity=[", fd);
	tmp = ft_ftoa(e->intensity);
	ft_putstr_fd(tmp, fd);
	free(tmp);
	ft_putendl_fd("]", fd);
	ft_putstr_fd("shadow=[", fd);
	if (e->s->shadow == 1)
		ft_putendl_fd("yes]", fd);
	else
		ft_putendl_fd("no]", fd);
	ft_putstr_fd("shine=[", fd);
	if (e->s->shine == 0)
		ft_putendl_fd("yes]", fd);
	else
		ft_putendl_fd("no]", fd);
}

void		write_cam_set(t_env *e, int fd)
{
	char	*tmp;

	tmp = ft_itoa(e->s->camx);
	ft_putstr_fd("camera=[", fd);
	ft_putstr_fd(tmp, fd);
	free(tmp);
	free_write(e->s->camy, fd, 0);
	free_write(e->s->camz, fd, 0);
	free_write(e->factx, fd, 0);
	free_write(e->facty, fd, 0);
	free_write(e->factz, 0, 0);
	ft_putendl_fd("]", fd);
}

char		*create_file(t_env *e, int conf_nb)
{
	int		fd;
	char	*tmp_fn;
	char	*filename;
	char	*tmp2;
	char	*tmp3;

	tmp3 = ft_strdup(".conf");
	tmp2 = ft_itoa(-conf_nb);
	tmp_fn = ft_strjoin(e->s->name, tmp2);
	free(tmp2);
	filename = ft_strjoin(tmp_fn, tmp3);
	free(tmp3);
	free(tmp_fn);
	if ((fd = open(filename, O_RDWR)) < 0)
	{
		if ((fd = open(filename, O_CREAT | O_WRONLY | S_IRWXU) < 0))
			ft_exit("Error while creating the new config file :(");
		conf_nb = -2;
	}
	if (conf_nb != -2)
		free(filename);
	close(fd);
	if (conf_nb > 49)
		return (NULL);
	return ((conf_nb != -2) ? create_file(e, conf_nb + 1) : filename);
}

void		write_in_file(t_env *e)
{
	int		fd;
	char	*filename;

	filename = create_file(e, 0);
	if ((fd = open(filename, O_RDWR)) < 0)
		ft_exit("Error while opening the new file, export spam +50 configs ?");
	else
	{
		ft_putstr(filename);
		ft_putendl(" generated !");
		ft_putstr_fd("scene_name=[", fd);
		ft_putstr_fd(e->s->name, fd);
		ft_putendl_fd("]", fd);
		write_cam_set(e, fd);
		write_win_set(e, fd);
		write_lights(e, fd, -1);
		write_planes(e, fd, -1);
		write_spheres(e, fd, -1);
		write_co_cy(e, fd, -1);
		write_hyper(e, fd, -1);
		free(filename);
		close(fd);
	}
}

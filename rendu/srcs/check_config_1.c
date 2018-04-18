/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 22:31:19 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/05 23:36:10 by jlajovec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

int			check_intensity(t_env *e, t_sce *s, int p, int x)
{
	int		len;
	int		j;

	j = 0;
	if (ft_strstr(e->map[p], "intensity=[") != NULL)
	{
		len = (int)ft_strlen(e->map[p]);
		s->tmp = NULL;
		if ((s->tmp = (char*)malloc(sizeof(char) * (len + 1))) == 0)
			ft_exit("Error malloc intensity.");
		while (e->map[p][x++])
			if (e->map[p][x - 1] == '[')
				while (e->map[p][x] != ']')
					s->tmp[j++] = e->map[p][x++];
		j = -1;
		while (s->tmp[++j])
			if ((!(ft_isdigit(s->tmp[j]))) && (s->tmp[j] != '.'))
				break ;
		e->intensity = ft_atof(s->tmp);
		free(s->tmp);
		return ((e->intensity > 0 && e->intensity <= 1) ? 0 : 1);
	}
	return (1);
}

void		stock_camera_2(t_sce *s, int coor_num)
{
	if (coor_num == 3)
		s->cam_normx = ft_atof(s->tmp);
	if (coor_num == 4)
		s->cam_normy = ft_atof(s->tmp);
	if (coor_num == 5)
		s->cam_normz = ft_atof(s->tmp);
}

int			stock_camera(t_sce *s, int coor_num, int j)
{
	s->tmp[j] = '\0';
	j = 0;
	while (s->tmp[j])
	{
		if ((s->tmp[j] < 48 || s->tmp[j] > 57) && (s->tmp[j] != '.')
			&& (s->tmp[j] != '-'))
			ft_exit("camera coordinates must be numerical");
		j++;
	}
	if (coor_num == 0)
		s->camx = ft_atof(s->tmp);
	if (coor_num == 1)
		s->camy = ft_atof(s->tmp);
	if (coor_num == 2)
		s->camz = ft_atof(s->tmp);
	stock_camera_2(s, coor_num);
	free(s->tmp);
	return (1);
}

int			check_camera(t_env *e, t_sce *s, int p, int x)
{
	int		len;
	int		j;

	j = 0;
	if (ft_strstr(e->map[p], "camera=[") != NULL && s->coor < 6)
	{
		len = (int)ft_strlen(e->map[p]);
		if ((s->tmp = (char*)malloc(sizeof(char) * (len + 1))) == 0)
			ft_exit("Error malloc camera.");
		while (e->map[p][x++] && x <= len && s->coor < 6)
			if (e->map[p][x - 1] == '[' || s->coor > 0)
				while (e->map[p][x] != ',' && e->map[p][x] != ']'
						&& s->coor < 6)
				{
					if (x < len)
						s->tmp[j++] = e->map[p][x++];
					if ((e->map[p][x] == ',' || x == len) && s->coor < 6)
					{
						s->coor += stock_camera(s, s->coor, j);
						check_camera(e, s, p, x + 1);
					}
				}
		return (0);
	}
	return (1);
}

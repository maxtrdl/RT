/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 23:45:57 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/05 23:27:17 by ggaudin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

int			stock_cone_colors(t_sce *s, int coor_num, int p)
{
	if (coor_num == 8)
	{
		s->forms[p]->col.r = ft_atof(s->tmp);
		if (s->forms[p]->col.r >= 0 && s->forms[p]->col.r <= 1)
			return (0);
		return (1);
	}
	if (coor_num == 9)
	{
		s->forms[p]->col.g = ft_atof(s->tmp);
		if (s->forms[p]->col.g >= 0 && s->forms[p]->col.g <= 1)
			return (0);
		return (1);
	}
	if (coor_num == 10)
	{
		s->forms[p]->col.b = ft_atof(s->tmp);
		if (s->forms[p]->col.b >= 0 && s->forms[p]->col.b <= 1)
			return (0);
		return (1);
	}
	return (0);
}

void		stock_cone2(t_sce *s, int coor_num, int p)
{
	int		ret;

	ret = 0;
	if (coor_num == 2)
		s->forms[p]->pos.z = ft_atof(s->tmp);
	if (coor_num == 3)
		s->forms[p]->norm.x = ft_atof(s->tmp);
	if (coor_num == 4)
		s->forms[p]->norm.y = ft_atof(s->tmp);
	if (coor_num == 5)
		s->forms[p]->norm.z = ft_atof(s->tmp);
	if (coor_num == 6)
		s->forms[p]->rad = ft_atof(s->tmp);
	if (coor_num == 7)
		s->forms[p]->high = ft_atof(s->tmp);
	if (coor_num == 8)
		ret = stock_cone_colors(s, coor_num, p);
	if (coor_num == 9)
		ret = stock_cone_colors(s, coor_num, p);
	if (coor_num == 10)
		ret = stock_cone_colors(s, coor_num, p);
	if (ret == 1)
		ft_exit("colors must be comprised between 0 and 1");
}

int			stock_cone(t_sce *s, int coor_num, int j, int p)
{
	s->tmp[j] = '\0';
	j = 0;
	while (s->tmp[j])
	{
		if ((s->tmp[j] < 48 || s->tmp[j] > 57) && (s->tmp[j] != '.') \
	&& (s->tmp[j] != '-'))
			ft_exit("cone coordinates must be numerical");
		j++;
	}
	if (coor_num >= 3 && coor_num <= 5)
	{
		if (ft_atof(s->tmp) < -1)
			s->tmp = ft_itoa(-1);
		else if (ft_atof(s->tmp) > 1)
			s->tmp = ft_itoa(1);
	}
	if (coor_num == 0)
		s->forms[p]->pos.x = ft_atof(s->tmp);
	if (coor_num == 1)
		s->forms[p]->pos.y = ft_atof(s->tmp);
	stock_cone2(s, coor_num, p);
	free(s->tmp);
	calcangle(s->forms[p]);
	return (1);
}

int			check_cone(t_env *e, t_sce *s, int p, int x)
{
	int		len;
	int		j;

	j = 0;
	if (s->coor < 11)
	{
		len = (int)ft_strlen(e->map[p]);
		if ((s->tmp = (char*)malloc(sizeof(char) * (len + 1))) == 0)
			ft_exit("error malloc");
		while (e->map[p][x++] && x <= len && s->coor < 11)
			if (e->map[p][x - 1] == '[' || s->coor > 0)
				while (e->map[p][x] != ',' && e->map[p][x] != ']' && \
						s->coor < 11)
				{
					if (x < len)
						s->tmp[j++] = e->map[p][x++];
					if ((e->map[p][x] == ',' || x == len) && s->coor < 11)
					{
						s->coor += stock_cone(s, s->coor, j, p - P_SCENE);
						check_cone(e, s, p, x + 1);
					}
				}
		return (final_check_forms(e, s, p, CONE));
	}
	return (1);
}

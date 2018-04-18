/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 22:26:10 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/05 23:20:23 by jlajovec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

float		dot2(t_vec a, t_vec b)
{
	float	ret;

	ret = (a.x * b.x) - (a.y * b.y) + (a.z * b.z);
	return (ret);
}

float		maxdata(float x, float y)
{
	if (x < y)
		return (y);
	return (x);
}

void		calcangle(t_form *f)
{
	t_vec	p1;
	t_vec	p2;
	float	d;
	t_vec	tmp;

	p1 = vec();
	p2 = vec();
	p1.x = f->pos.x + f->rad;
	p1.y = f->pos.y;
	p1.z = f->pos.z;
	p2.x = f->pos.x;
	p2.y = f->pos.y + f->high;
	p2.z = f->pos.z;
	tmp = vec();
	tmp = vec_sub(&p2, &p1);
	d = sqrtf((tmp.x * tmp.x) + (tmp.y * tmp.y) + (tmp.z * tmp.z));
	f->cos = f->high / d;
	f->sin = f->rad / d;
}

void		post_calc_aa(t_env *e, int x, int y)
{
	int		yi;
	int		xi;
	float	div;
	float	coef;
	t_col	c;

	c = col();
	xi = (-1 > x - 2) ? -1 : x - 2;
	div = 0;
	while (++xi < (e->width < (x + 2) ? e->width : x + 2))
	{
		yi = (-1 > y - 2) ? -1 : y - 2;
		while (++yi < (e->height < (y + 2) ? e->height : y + 2))
		{
			coef = (xi == x && yi == y) ? 5 : 1;
			c.r = c.r + e->image[xi][yi].r * coef;
			c.g = c.g + e->image[xi][yi].g * coef;
			c.b = c.b + e->image[xi][yi].b * coef;
			div = div + coef;
		}
	}
	e->image[x][y].r = c.r / div;
	e->image[x][y].g = c.g / div;
	e->image[x][y].b = c.b / div;
}

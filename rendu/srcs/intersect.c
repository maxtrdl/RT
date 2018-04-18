/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 23:25:49 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/05 20:10:08 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

int		intersect_plane(t_env *e, t_vec **rayo, t_vec **raydir, t_form *f)
{
	float	denom;
	float	result;

	denom = dot(**raydir, f->norm);
	if (fabsf(denom) < 1e-6)
		return (0);
	else
	{
		result = dot((vec_sub(&f->pos, *rayo)), f->norm) / denom;
		e->t0 = result;
		if (e->t0 == 0.00)
			return (0);
		if (e->t0 > 0.00)
			return (1);
	}
	return (0);
}

int		resolve_quadratic(t_env *e, float det, float a, float b)
{
	float	sqr;
	int		ret_value;

	ret_value = 0;
	sqr = sqrt(det);
	e->t1 = (-b + sqr) / (2. * a);
	e->t2 = (-b - sqr) / (2. * a);
	if (e->t1 > 0.1f && e->t1 < e->mint)
	{
		e->t0 = e->t1;
		ret_value = 1;
	}
	if (e->t2 > 0.1f && e->t2 < e->mint)
	{
		e->t0 = e->t2;
		ret_value = 1;
	}
	return (ret_value);
}

void	ft_swap(t_env *e)
{
	float tmp;

	tmp = e->t1;
	e->t1 = e->t2;
	e->t2 = tmp;
}

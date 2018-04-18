/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrudel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 23:53:08 by mtrudel           #+#    #+#             */
/*   Updated: 2018/03/05 23:55:54 by mtrudel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

int		intersect_hyperboloid(t_env *e, t_vec **rayo, t_vec **raydir, t_form *f)
{
	float	abc[3];
	float	tmp[2];
	float	discr;
	t_vec	dist;

	dist = vec_sub(&**rayo, &f->pos);
	tmp[0] = dot(**raydir, f->norm);
	tmp[1] = dot(dist, f->norm);
	abc[0] = dot2(**raydir, **raydir) - pow(tmp[0], 2.);
	abc[1] = 2. * (dot2(dist, **raydir) - (tmp[0] * tmp[1]));
	abc[2] = dot2(dist, dist) - pow(tmp[1], 2.) - pow(f->rad, 2.);
	discr = abc[1] * abc[1] - (4. * abc[0] * abc[2]);
	if (discr < 0.)
		return (0);
	else
	{
		if (resolve_quadratic(e, discr, abc[0], abc[1]) == 1)
			return (1);
	}
	return (0);
}

int		intersect_cylinder(t_env *e, t_vec **rayo, t_vec **raydir, t_form *f)
{
	float	abc[3];
	float	tmp[2];
	float	discr;
	t_vec	dist;

	dist = vec_sub(&**rayo, &f->pos);
	tmp[0] = dot(**raydir, f->norm);
	tmp[1] = dot(dist, f->norm);
	abc[0] = dot(**raydir, **raydir) - pow(tmp[0], 2.);
	abc[1] = 2. * (dot(**raydir, dist) - (tmp[0] * tmp[1]));
	abc[2] = dot(dist, dist) - pow(tmp[1], 2.) - pow(f->rad, 2.);
	discr = abc[1] * abc[1] - (4. * abc[0] * abc[2]);
	if (discr >= 0. && f->high >= 0.)
	{
		if (f->high > 0 && resolve_quadratic(e, discr, abc[0], abc[1]) == 1)
		{
			ft_swap(e);
			if ((e->t0 = intersect_caps(e, *rayo, *raydir, f)) != 0)
				return (1);
		}
		else if (resolve_quadratic(e, discr, abc[0], abc[1]) == 1)
			return (1);
	}
	return (0);
}

int		intersect_cone(t_env *e, t_vec **rayo, t_vec **raydir, t_form *f)
{
	float	abc[3];
	float	rad;
	float	discr;
	float	tmp[2];
	t_vec	dist;

	rad = (f->rad * (M_PI / 180)) * 4;
	dist = vec_sub(&**rayo, &f->pos);
	tmp[0] = dot(**raydir, f->norm);
	tmp[1] = dot(dist, f->norm);
	abc[0] = dot(**raydir, **raydir) - ((1 + pow(rad, 2)) * pow(tmp[0], 2));
	abc[1] = 2 * (dot(**raydir, dist) - ((1 + pow(rad, 2)) * tmp[0] * tmp[1]));
	abc[2] = dot(dist, dist) - ((1 + pow(rad, 2)) * pow(tmp[1], 2));
	discr = abc[1] * abc[1] - (4. * abc[0] * abc[2]);
	if (discr < 0. || f->high < 0.)
		return (0);
	if (f->high > 0 && resolve_quadratic(e, discr, abc[0], abc[1]) == 1)
	{
		ft_swap(e);
		if ((e->t0 = intersect_caps(e, *rayo, *raydir, f)) != 0)
			return (1);
	}
	else if (resolve_quadratic(e, discr, abc[0], abc[1]) == 1)
		return (1);
	return (0);
}

int		intersect_sphere(t_env *e, t_vec **rayo, t_vec **raydir, t_form *f)
{
	t_vec	l;
	float	s2;
	float	s;
	float	t0;

	l = vec();
	l = vec_sub(&f->pos, *rayo);
	e->tca = 0;
	e->tca = dot(l, **raydir);
	if (e->tca < 0.00)
		return (0);
	else
	{
		s2 = (dot(l, l)) - (e->tca * e->tca);
		s = sqrt(s2);
		if (s > f->rad)
			return (0);
		else
		{
			e->thc = sqrt((f->rad * f->rad) - s2);
			t0 = e->tca - e->thc;
			e->t0 = t0;
		}
	}
	return (1);
}

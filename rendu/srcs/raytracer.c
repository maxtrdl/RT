/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 23:58:39 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/05 20:07:29 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

int			intersect(t_env *e, t_vec *rayo, t_vec *raydir, t_form *f)
{
	if (f->form_id == SPHERE)
		return (intersect_sphere(e, &rayo, &raydir, f));
	else if (f->form_id == PLANE)
		return (intersect_plane(e, &rayo, &raydir, f));
	else if (f->form_id == CONE)
		return (intersect_cone(e, &rayo, &raydir, f));
	else if (f->form_id == CYLINDER)
		return (intersect_cylinder(e, &rayo, &raydir, f));
	else if (f->form_id == HYPERBOL)
		return (intersect_hyperboloid(e, &rayo, &raydir, f));
	return (0);
}

void		do_hit(t_env *e, int k, int hit)
{
	if (hit && e->t0 < e->mint)
	{
		e->mint = e->t0;
		e->form_hit = k;
	}
}

void		raytracer_routine(t_env *e)
{
	int		hit;
	int		k;

	k = e->r[0]->s->nb_lights - 1;
	raytracer_loop(e, e->i, e->j);
	while (++k < e->r[0]->nb_forms)
	{
		hit = intersect(e, &e->rayo, &e->raydir, e->r[0]->s->forms[k]);
		do_hit(e, k, hit);
	}
	levels(e);
	if (e->form_hit == -1 && e->r[0]->lev != 3)
	{
		e->r[0]->image[e->i][e->j].r = 0;
		e->r[0]->image[e->i][e->j].g = 0;
		e->r[0]->image[e->i][e->j].b = 0;
	}
}

void		*raytracer(void *arg)
{
	t_env	*e;

	e = (struct s_env *)arg;
	e->i = (e->r[0]->width / NBTHREAD) * e->t;
	init_raytracer(e);
	while (e->i < e->r[0]->width)
	{
		e->j = -1;
		while (++e->j < e->r[0]->height)
		{
			raytracer_routine(e);
		}
		e->i++;
		if (((e->i % ((int)e->r[0]->width / NBTHREAD)) == 0) && e->i > 1)
		{
			pthread_exit(NULL);
			return (NULL);
		}
	}
	pthread_exit(NULL);
	return (NULL);
}

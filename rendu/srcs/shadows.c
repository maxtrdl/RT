/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 12:03:05 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/06 15:58:46 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

static void	init_shadow(t_env *e, int i, t_vec *tmp1)
{
	e->mint = INFINITY;
	lightset(e, i);
	e->p0 = vec_add(&e->rayo, tmp1);
	norm_init(e);
}

static int	hitshadow(t_env *e, int l, int lighthit)
{
	int		res;
	t_vec	tmp2;

	res = -1;
	while (l < e->r[0]->nb_forms)
	{
		if (e->r[0]->s->forms[l]->form_id != PLANE)
		{
			lighthit = 0;
			tmp2.x = e->normal.x * 1e-4f + e->p0.x;
			tmp2.y = e->normal.y * 1e-4f + e->p0.y;
			tmp2.z = e->normal.z * 1e-4f + e->p0.z;
			if (l != e->form_hit)
				lighthit = intersect(e, &tmp2, &e->lightray, \
					e->r[0]->s->forms[l]);
			if (lighthit && e->t0 < e->mint)
			{
				e->mint = e->t0;
				res = l;
			}
		}
		l++;
	}
	return (res);
}

static void	putshadow(t_env *e)
{
	if (e->red >= 0.05 && e->green >= 0.05 && e->blue >= 0.05)
	{
		e->red -= 0.05;
		e->green -= 0.05;
		e->blue -= 0.05;
	}
	e->r[0]->image[e->i][e->j].r = e->red;
	e->r[0]->image[e->i][e->j].g = e->green;
	e->r[0]->image[e->i][e->j].b = e->blue;
}

void		shadow(t_env *e)
{
	int		light_form_hit;
	int		l;
	t_vec	tmp1;
	int		i;

	e->red = e->red * 0.5;
	e->green = e->green * 0.5;
	e->blue = e->blue * 0.5;
	tmp1 = prod_matr(e->mint, &e->raydir);
	i = -1;
	light_form_hit = -1;
	while (++i < e->r[0]->nb_forms)
		if (e->r[0]->s->forms[i]->form_id == LIGHT)
		{
			init_shadow(e, i, &tmp1);
			light_form_hit = -1;
			l = e->r[0]->s->nb_lights;
			light_form_hit = hitshadow(e, l, 0);
			if (light_form_hit != -1)
				putshadow(e);
		}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 00:04:27 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/05 16:31:51 by jlajovec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

t_env	*init_struct(t_env *e)
{
	e->pcamspace = vec();
	e->raydir = vec();
	return (e);
}

void	threads_launch(t_env *e)
{
	e->t = -1;
	while (++e->t < NBTHREAD)
	{
		if (e->inits == 0)
		{
			e->r[e->t] = ft_memalloc(sizeof(t_env));
			e->r[e->t] = init_struct(e->r[e->t]);
			e->r[e->t]->r[0] = e;
		}
		e->r[e->t]->t = e->t;
		if (pthread_create(&e->thread[e->t], NULL, raytracer, e->r[e->t]) != 0)
			ft_exit("Error while creating a thread");
	}
	e->t = -1;
	while (++e->t < NBTHREAD)
		pthread_join(e->thread[e->t], NULL);
	put_pixel(e, 0, e->width);
	e->inits = 1;
	aff_img(e);
}

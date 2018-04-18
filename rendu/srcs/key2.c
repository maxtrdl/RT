/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaudin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 23:20:39 by ggaudin-          #+#    #+#             */
/*   Updated: 2018/03/06 17:53:58 by agaspard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

int			keyhook7(int k, int re, t_env *e)
{
	if (k == K_O)
	{
		if (e->s->shadow == 0)
			e->s->shadow = 1;
		else if (e->s->shadow == 1)
			e->s->shadow = 0;
	}
	if (k == K_DEL && e->choice != -1)
	{
		e->s->forms[e->choice]->form_id = -1;
		e->choice = -1;
	}
	if (k == K_SPC && e->lev == -1)
	{
		e->rt_activate = 1;
		e->lev = 1;
	}
	if (k == K_R && e->lev == 2)
		e->reflet = e->reflet > 1.5 ? 0.5 : e->reflet + 0.1;
	if (k == K_O || k == K_DEL || k == K_SPC || k == K_R)
		re++;
	return (re);
}

int			keyhook6(int k, int re, t_env *e)
{
	if (k == 18 || k == 19)
	{
		if (k == 18)
			e->choice--;
		if (k == 19)
			e->choice++;
		if (e->choice >= e->s->nb_lights)
			e->choice = e->s->nb_lights - 1;
		if (e->choice < 0)
			e->choice = 0;
		re++;
	}
	return (re + keyhook7(k, re, e));
}

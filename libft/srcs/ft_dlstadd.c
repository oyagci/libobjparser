/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:06:19 by oyagci            #+#    #+#             */
/*   Updated: 2017/02/06 14:14:04 by oyagci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void			ft_dlstadd(t_dlist **alst, t_dlist *elem)
{
	if (*alst)
	{
		elem->next = *alst;
		elem->prev = (*alst)->prev;
		(*alst)->prev = elem;

		if (elem->prev) {
			elem->prev->next = elem;
		}
		*alst = elem;
	}
	else
	{
		elem->next = NULL;
		elem->prev = NULL;
		*alst = elem;
	}
}

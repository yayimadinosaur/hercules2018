/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stables.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfung <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:31:57 by wfung             #+#    #+#             */
/*   Updated: 2018/03/23 15:55:27 by wfung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

typedef struct 			s_unrolled {
	struct s_unrolled*	next;
	unsigned			count;
	int				values[8]; //0-7
} 						t_unrolled;

t_unrolled* new_unrolled(void) {
	t_unrolled*	new = malloc(sizeof(t_unrolled));
	//here
	new->next = NULL;
	new->count = 0;
	return new;
}

long	sum_unrolled(t_unrolled* list) {
	long		sum;
	int			size;
	sum = 0;
	while (list)
	{
		size = list->count;	//always 8
		do {
			sum += list->values[--size]; //add all 8 to sum //total is 42 * 8
		} while (size != 0);
		list = list->next;
	}
	return (sum);
}

void	del_unrolled(t_unrolled* list)
{
	(void)list;
	t_unrolled *head = list; //
	t_unrolled *tmp	= list;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
	//free stuff here?
}

int		main(void) {
	t_unrolled*	list;
	t_unrolled*	tmp;
	int			val;
	unsigned	i;
	long long	magic;

	magic = 753057078882375803;
	val = 0;
	i = 0;
	list = NULL;
	while (i < 42)
	{
		tmp = new_unrolled();	//every mallo happens here
		while (tmp->count < 8)
		{
			tmp->values[tmp->count] = val++;
			++tmp->count;
		}
		++i;
		if (!list)
			list = tmp;
		else
		{
			tmp->next = list;
			list = tmp;
		}			
	}
	magic += sum_unrolled(list);
	write(1, &magic, 8);
	del_unrolled(list);
	return(0);
}

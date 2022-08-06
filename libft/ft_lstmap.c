/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joctopus <joctopus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 20:42:03 by joctopus          #+#    #+#             */
/*   Updated: 2021/10/23 17:01:49 by joctopus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
 * ? lst - adress of pointer to an element;
 * ? void *(*f)(void *) - adress of function used to iterate on the list; 
 * ? void (*del)(void *) - function used to delete the content of 
 * ? an element if needed;
 * 
 ** return value: New list. NULL if allocation fails
 * 
 * Iterates the list ’lst’ and applies the function
 * ’f’ to the content of each element. Creates a new
 * list resulting of the successive applications of
 * the function ’f’. The ’del’ function is used to
 * delete the content of an element if needed.
 **/

static t_list	*ft_check(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_elem;

	new_elem = ft_lstnew(f(lst->content));
	if (!new_elem)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	return (new_elem);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elem;

	if (!lst || !f)
		return (NULL);
	new_elem = ft_check(lst, f, del);
	new_lst = new_elem;
	lst = lst->next;
	while (lst)
	{
		new_elem = ft_lstnew(f(lst->content));
		if (!(new_elem))
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&new_lst, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&new_lst, new_elem);
	}
	return (new_lst);
}

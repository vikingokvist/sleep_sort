
#include "sleep_sort.h"

t_list	*lnkdlstnew(int value)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->index = -1;
	new_node->next = NULL;
	return (new_node);
}

void	lnkdlstadd_back(t_list **list, t_list *newl)
{
	t_list	*last;

	if (!list || !newl)
		return ;
	if (!*list)
	{
		*list = newl;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = newl;
}

void	lnkdlst_free(t_list **list)
{
	t_list	*temp;

	while (*list)
	{
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
	free(list);
}

void	lnkdlst_index(t_list **list)
{
	t_list	*current;
	t_list	*stack_dupe;
	int		count;

	current = *list;
	while (current != NULL)
	{
		count = 1;
		stack_dupe = *list;
		while (stack_dupe != NULL)
		{
			if (current->value > stack_dupe->value)
				count++;
			stack_dupe = stack_dupe->next;
		}
		current->index = count;
		current = current->next;
	}
}

size_t	lnkdlst_len(t_list **list)
{
	size_t	len;
	t_list	*current;

	len = 0;
	current = *list;
	while (current != NULL)
	{
		current = current->next;
		len++;
	}
	return (len);
}

void	lnkdlst_print(t_list **list)
{
	t_list	*temp;

	temp = *list;
	while (temp)
	{
		printf("%d\n", temp->value);
		temp = temp->next;
	}
	// printf("NULL\n");
}
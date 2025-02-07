#ifndef SLEEP_SORT_H
# define SLEEP_SORT_H

# define _XOPEN_SOURCE 600
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <stdlib.h>

# define ERR_ARGS "Usage: ./sleep_sort 9 5 4 1 8 5 3...\n"
# define ERR_THREAD_CREATE "Error creating threads.\n"
# define ERR_THREAD_JOIN "Error joining threads.\n"

typedef struct s_list
{
	int				value;
	int				index;
	struct s_list	*next;
}	t_list;


int main(int argc, char **argv);
void    *sleep_sort(void *param);
int init_threads(t_list **list);
void lnkdlst_append(t_list *list);
t_list	*lnkdlstnew(int value);
void	lnkdlstadd_back(t_list **list, t_list *newl);
void	lnkdlst_index(t_list **list);
void	lnkdlst_print(t_list **list);
size_t	lnkdlst_len(t_list **list);
void	lnkdlst_free(t_list **list);

#endif
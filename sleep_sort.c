#include "sleep_sort.h"

pthread_barrier_t   barrier;
pthread_mutex_t     append_lock;
t_list **sorted_list = NULL;

void lnkdlst_append(t_list *list)
{
    t_list *new_node;

    pthread_mutex_lock(&append_lock);
    if (!sorted_list)
    {
        sorted_list = malloc(sizeof(t_list *));
        if (!sorted_list)
        {
            pthread_mutex_lock(&append_lock);
            return ;
        }
        *sorted_list = lnkdlstnew(list->value);
    }
    else
    {
        new_node = lnkdlstnew(list->value);
        lnkdlstadd_back(sorted_list, new_node);
    }
    pthread_mutex_unlock(&append_lock);
}

void    *sleep_sort(void *param)
{
    t_list  *node;

    node = (t_list *)param;
    pthread_barrier_wait(&barrier);
    sleep(node->index);
    lnkdlst_append(node);
    return (NULL);
}

int init_threads(t_list **list)
{
    int     list_len = lnkdlst_len(list);
    pthread_t   threads[list_len];
    int         i = 0;
    t_list      *cur = *list;

    pthread_barrier_init(&barrier, NULL, list_len);
    pthread_mutex_init(&append_lock, NULL);
    while (cur)
    {
        if (pthread_create(&threads[i], NULL, &sleep_sort, (void *)cur) != 0)
            return (printf(ERR_THREAD_CREATE), 1);
        cur = cur->next;
        i++;
    }
    i = 0;
    while (i < list_len)
    {
        if (pthread_join(threads[i], NULL) != 0)
            return (printf(ERR_THREAD_JOIN), 1);
        i++;
    }
    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&append_lock);
    return (0);
}

int main(int argc, char **argv)
{
    t_list **list =  malloc(sizeof(t_list *)); if (!list) return (1);
    t_list *new_node;
    int     i;

    if (argc < 2)
        return (printf(ERR_ARGS), 1);
    *list = NULL;
    i = 1;
    while (i < argc)
	{
		new_node = lnkdlstnew(atol(argv[i]));
		lnkdlstadd_back(list, new_node);
		i++;
	}
    lnkdlst_index(list);
    lnkdlst_print(list);
    if (init_threads(list))
    {
        lnkdlst_free(list);
        return (1);
    }
    lnkdlst_free(list);
    lnkdlst_print(sorted_list);
    lnkdlst_free(sorted_list);
    return (0);
}


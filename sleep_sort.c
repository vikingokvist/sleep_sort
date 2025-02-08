#include "sleep_sort.h"

pthread_barrier_t   barrier;
pthread_mutex_t     append_lock;
t_list              **sorted_list = NULL;

void    *sleep_sort_routine(void *param)
{
    t_list  *node;
    t_list  *sorted_node;

    node = (t_list *)param;
    pthread_barrier_wait(&barrier);
	usleep(node->index * 10000);
    pthread_mutex_lock(&append_lock);
    if (!sorted_list)
    {
        sorted_list = malloc(sizeof(t_list *));
        if (!sorted_list)
            return (pthread_mutex_lock(&append_lock), NULL);
        *sorted_list = lnkdlstnew(node->value);
    }
    else
    {
        sorted_node = lnkdlstnew(node->value);
        lnkdlstadd_back(sorted_list, sorted_node);
    }
    pthread_mutex_unlock(&append_lock);
    return (NULL);
}

t_list **sleep_sort(t_list **list)
{
    int         list_len = lnkdlst_len(list);
    pthread_t   threads[list_len];
    t_list      *cur = *list;
    int         i = 0;

    pthread_barrier_init(&barrier, NULL, list_len);
    pthread_mutex_init(&append_lock, NULL);
    while (cur)
    {
        if (pthread_create(&threads[i], NULL, &sleep_sort_routine, (void *)cur) != 0)
            return (printf(ERR_THREAD_CREATE), NULL);
        cur = cur->next;
        i++;
    }
    i = 0;
    while (i < list_len)
    {
        if (pthread_join(threads[i], NULL) != 0)
            return (printf(ERR_THREAD_JOIN), NULL);
        i++;
    }
    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&append_lock);
    return (sorted_list);
}

int main(int argc, char **argv)
{
    t_list **list =  malloc(sizeof(t_list *)); if (!list) return (1); *list = NULL;
    t_list **sorted_list = NULL;
    t_list *new_node = NULL;

    if (argc < 2)
        return (printf(ERR_ARGS), 1);
    for (int i = 1; i < argc; i++)
	{
		new_node = lnkdlstnew(atol(argv[i]));
		lnkdlstadd_back(list, new_node);
	}
    lnkdlst_index(list);
    lnkdlst_print(list);
    sorted_list = sleep_sort(list);
    if (!sorted_list)
        return (lnkdlst_free(list), 1);
    lnkdlst_free(list);
    lnkdlst_print(sorted_list);
    lnkdlst_free(sorted_list);
    return (0);
}


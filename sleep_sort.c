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

t_list **sleep_sort(t_list **list, unsigned int list_len)
{
    pthread_t   threads[list_len];
    t_list      *cur = *list;
    unsigned int i = 0;

    if (!list || !list_len)
        return (NULL);
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

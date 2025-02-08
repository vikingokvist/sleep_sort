#include "sleep_sort.h"

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
    sorted_list = sleep_sort(list, lnkdlst_len(list));
    if (!sorted_list)
        return (lnkdlst_free(list), 1);
    lnkdlst_free(list);
    lnkdlst_print(sorted_list);
    lnkdlst_free(sorted_list);
    return (0);
}

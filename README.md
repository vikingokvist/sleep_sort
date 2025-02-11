# Sleep Sort

## Description
Sleep Sort is a unique sorting algorithm that sorts a linked list using threads and usleep(). Instead of sleeping based on the actual value of each node, it sleeps according to a computed index, ensuring it works with negative numbers as well.

### How It Works
- Assigns an index to each node based on how many values are smaller than it. This ensures that the sorting mechanism works regardless of negative numbers.  
- Each thread calls sleep_sort_routine(); 
- The thread sleeps for index * 10000 microseconds (* 10000 for precision).  
- After waking, it appends its value to a new global linked list.  
- The sorted linked list is returned, while the original list must be freed manually.  

### Performance
- 500 numbers sorted in ~0.01ms due to minimal sleep delay.  
- Efficient when used with relatively small numbers due to the sleep-based approach.  
- Thread overhead may impact performance for large datasets.  

### Functions  
`t_list **sleep_sort(t_list **list, unsigned int list_len)`  
- Sorts a linked list using Sleep Sort.  
- Returns a new sorted linked list.  
- Requires the original list to be freed manually.

`void *sleep_sort_routine(void *param)`  
- Sleeps based on index value.  
- Appends the node value to a global linked list after waking.  

`void lnkdlst_index(t_list **list)`  
- Assigns an index to each node based on its relative position.  

`void lnkdlstadd_back(t_list **list, t_list *newl)`  
- Appends a node to the end of a linked list.  

`t_list *lnkdlstnew(int value)`  
- Creates a new linked list node.  

`void lnkdlst_free(t_list **list)`  
- Frees the memory allocated for a linked list.  

`size_t lnkdlst_len(t_list **list)`  
- Returns the length of a linked list.  

`void lnkdlst_print(t_list **list)`  
- Prints a linked list for debugging.  

### Notes  
- Uses pthread_barrier_t to synchronize thread execution before sleeping.  
- Uses pthread_mutex_t to ensure safe access to the global sorted list.  
- Sorting time depends on the largest index assigned.  
- Works with negative numbers due to index-based sorting instead of direct value-based sorting.  

#include "memory_pool.h"
NAME::memory_pool::memory_pool()
{
    for(int i = 0 ; i < SIZE_OF_FREE_LISTS; i++)
        pool[i] = enlarge( (i+1) * BLOCK_STEP);
}
void* NAME::memory_pool::allocate(size_type n)
{
    int order = n / BLOCK_STEP;
    free_list_node *empty = pool[order];
    void* result;
    if(empty == nullptr)
    {
        empty = enlarge(floor(n));
        pool[order] = empty->next;
    }
    result = empty->block;
    delete empty;
    return result;
}
bool NAME::memory_pool::deallocate(void* p, size_type n)
{
    auto temp = new free_list_node;
    temp->block = p;
    int order = n / BLOCK_STEP;
    temp->next = pool[order];
    pool[order] = temp;
}
int NAME::memory_pool::floor(size_type n)
{
    return n / BLOCK_STEP + 1;
}
NAME::free_list_node* NAME::memory_pool::enlarge(size_type n)
{
    NAME::free_list_node* prev, *p, *head;
    head = nullptr;
    for(int i = 0; i < NUMBER_OF_BLOCKS_PER_STEP ; i ++)
    {   
        p = new free_list_node;
        p->block = (void*)malloc(sizeof(unsigned char)*n);
        p->next = nullptr;
        if(head == nullptr) head = p;
        prev->next = p;
        prev = p;
    }
    return head;
}
#include "memory_pool.h"

using namespace JJ;


memory_pool::memory_pool()
{
    //
    for(int i = 0 ; i < SIZE_OF_FREE_LISTS; i++)
        pool[i] = enlarge( (i+1) * BLOCK_STEP);
}
void* memory_pool::allocate(size_t n)
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
void memory_pool::deallocate(void* p, size_t n)
{
    auto temp = new free_list_node;
    temp->block = p;
    int order = n / BLOCK_STEP;
    temp->next = pool[order];
    pool[order] = temp;
}
size_t memory_pool::floor(size_t n)
{
    return n / BLOCK_STEP + 1;
}
free_list_node* memory_pool::enlarge(size_t n)
{
    free_list_node* prev, *p, *head;
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

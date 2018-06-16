#pragma once
#include <cstdlib>
#define BLOCK_STEP 8
#define SIZE_OF_FREE_LISTS 16
#define TYPE_SIZE_THRESHOLD SIZE_OF_FREE_LISTS*BLOCK_STEP
#define NUMBER_OF_BLOCKS_PER_STEP 20
#define NAME jj
namespace NAME
{
    class memory_pool
    {
        typedef size_t size_type;
    public:
        static free_list_node* pool [SIZE_OF_FREE_LISTS];
        memory_pool();
        void* allocate(size_type n);
        bool deallocate(void* p, size_type n);
    private:
        int floor(size_type n);
        free_list_node* enlarge(size_type n);
    };
    struct free_list_node
    {
    public:
        void* block;
        free_list_node* next;
    };
};

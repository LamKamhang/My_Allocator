#pragma once
#include <cstdlib>



namespace JJ
{
    #define BLOCK_STEP 8
    #define SIZE_OF_FREE_LISTS 16
    #define TYPE_SIZE_THRESHOLD SIZE_OF_FREE_LISTS*BLOCK_STEP
    #define NUMBER_OF_BLOCKS_PER_STEP 100

    struct free_list_node
    {
        void* block;
        free_list_node* next;
    };

    class memory_pool
    {
    public:
        memory_pool();
        void* allocate(size_t n);
        void deallocate(void* p, size_t n);
    private:
		free_list_node* pool[SIZE_OF_FREE_LISTS];
        size_t floor(size_t n);
        free_list_node* enlarge(size_t n);
    };
    
    
};

extern JJ::memory_pool mp;
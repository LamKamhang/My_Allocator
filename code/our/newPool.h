/*
* File: newPool.h
* Version: 1.0
* Author: kk
* Created Date: Tue Jun 19 16:53:17 DST 2018
* -------------------------------------------
* 内存池的声明
* version 1.0: 尝试实现一个奇技淫巧
*/
#pragma once

#include <cstdlib>
#include <map>
#include <iostream>

namespace JJ
{
    #define BLOCK_STEP 16

    class MyMemPool
    {
    public:
        // first, malloc a big pool for further use.
        MyMemPool():i(0){pool = (char *)malloc(sizeof(int)*0xfffffff);};
        ~MyMemPool(){free(pool);};

        // when want to allocate, just give the origin part and divide it.
        void* allocate(size_t n)
        {
            size_t order = _round(n);
            if (free_list.find(order) != free_list.end() && free_list[order] != nullptr)
            {
                free_list_node *node = free_list[order];
                free_list[order] = node->next;
                return (void *)node;
            }
            else if (i + order < 0xfffffff)
            {
                size_t index = i;
                i = i + order;
                return (void *)(pool + index);
            }
            else
            {
                return (void *)malloc(n);
            }

            //  if (i + order < 0xfffffff)
            // {
            //     size_t index = i;
            //     i = i + order/sizeof(int);
            //     return (void *)(pool + index);
            // }
            // else if (free_list.find(order) != free_list.end() && free_list[order] != nullptr)
            // {
            //     free_list_node *node = free_list[order];
            //     free_list[order] = node->next;
            //     return (void *)node;
            // }
            // else
            // {
            //     return (void *)malloc(n);
            // }
        }

        // deallocate, just give it into the free_list.
        void deallocate(void* p, size_t n)
        {
            size_t order = _round(n);
            if (free_list.find(order) == free_list.end())
            {
                free_list[order] = (free_list_node*)p;
                free_list[order]->next = nullptr;
            }
            else{
                ((free_list_node*)p)->next = free_list[order];
                free_list[order] = (free_list_node*)p;
            }
        }
    private:
        union free_list_node{
            free_list_node *next;
        };
        char* pool;
        size_t i;
        std::map<size_t, free_list_node*> free_list;
        inline size_t _round(size_t n)
        {
            	/*_round向上取整,
                    example: BLOCK_STEP = 8
                        n		round
                        1		((1-1)/8 + 1) * 8 = 8
                        7		((7-1)/8 + 1) * 8 = 8
                        8		((8-1)/8 + 1) * 8 = 8
                        9		((9-1)/8 + 1) * 8 = 16
                */
	    return ((n - 1) / BLOCK_STEP + 1) * BLOCK_STEP;
        }
    };
}

/*
* File: myMemPool.cpp
* Version: 1.1
* Author: dong, kk
* Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
* Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
* -------------------------------------------
* 内存池的实现
* version 1.0: 实现内存池的基本操作，使用预先申请内存进行内存分配(dong)
* version 1.1: 改造free_list_node的类型，使用联合减少内存消耗(kk)
*/
#include "Header/myMemPool.h"

using namespace JJ;

MyMemPool::MyMemPool()
{
	for (int i = 0; i < SIZE_OF_FREE_LISTS; ++i)
		pool[i] = _enlarge((i + 1) * BLOCK_STEP);
		//pool[i] = nullptr;
}
/*
* Function: ~MyMemPool
* Destructor
* Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
* Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
* ---------------------------------------------
* 析构函数，在析构的时候自动销毁释放内存池的信息
*/
MyMemPool::~MyMemPool()
{
	free_list_node* free_ptr;
	for (int i = 0; i < SIZE_OF_FREE_LISTS; ++i)
	{
		free_list_node* ptr = pool[i];
		while (ptr != nullptr)
		{
			free_ptr = ptr;
			ptr = ptr->next;
			free(free_ptr);
		}
	}
}

void* MyMemPool::allocate(size_t n)
{
	// 找到对应的链
	size_t order = n / BLOCK_STEP;

	// 全部被占用了
	if (pool[order] == nullptr)
	{
		// 重新申请一大块内存
		pool[order] = _enlarge(_round(n));
	}

	// 没有考虑申请内存失败的异常情况
	free_list_node* _slot = pool[order];
	pool[order] = _slot->next;
	return (void *)_slot;
}
void MyMemPool::deallocate(void* p, size_t n)
{
	// 如果p不是nullptr
	if (p != nullptr)
	{
		// order是对应的链下标, 以头插入的方式插入
		size_t order = n / BLOCK_STEP;
		((free_list_node *)p)->next = pool[order];
		pool[order] = (free_list_node*)p;
	}
}

/*
* Function: _round
* Argument: n(size_t) 需要申请的内存大小
* Return: _round(size_t) 标准化向上取整内存大小
* Usage: size_t normalize_n = _round(n);
* Create Date: Sun Jun 17 09:32:21 DST 2018(kk)
* ---------------------------------------------
* 因为内存池中的块大小是有间隔，8Byte为单位,(BLOCK_STEP)
* 这个函数的功能是将非标准的大小round到标准大小中，
* 向上取整。
*/
size_t MyMemPool::_round(size_t n)
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

/*
* Function: _enlarge
* Argument: n(size_t) 标准内存大小(8的倍数, 单位为Byte)
* Return: pointer(free_list_node*), 返回首地址
* Usage: free_list_node * ptr = _enlarge(_round(n)*BLOCK_STEP);
* Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
* Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
* -----------------------------------------------
* 实际去申请内存的函数，一次性申请20块作为链表返回
* 为了方便操作, 链表使用了头插入的方式
*/
MyMemPool::free_list_node* MyMemPool::_enlarge(size_t n)
{
	free_list_node *ptr, *head;
	head = ptr = nullptr;

	for (int i = 0; i < NUMBER_OF_BLOCKS_PER_STEP; ++i)
	{
		ptr = (free_list_node *)malloc(n);
		ptr->next = head;
		head = ptr;
	}

	return head;
}

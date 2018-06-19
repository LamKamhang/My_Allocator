
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
#include "myMemPool.h"

using namespace JJ;

MyMemPool::MyMemPool()
{
	for (int i = 0; i < SIZE_OF_FREE_LISTS; ++i)
		BlockPool[i] = _enlarge(i);
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
	free_list_node* temp;
	for(int i = 0; i < BLOCK_WIDTH; i++)
		free(BlockPool[i]);
	for(int i = 0; i < SIZE_OF_FREE_LISTS; i++)
		while(ListPool[i] != nullptr)
		{
			temp = ListPool[i];
			ListPool[i] = ListPool[i]->next;
			free(temp);
		}
}

void* MyMemPool::allocate(size_t n)
{
	// 找到对应的链
	size_t order = n / BLOCK_STEP;
	void* result;
	// 如果散链没有内存
	if (ListPool[order] == nullptr)
	{
		// 看看有没有老本
		// 如果没有老本，申请老本
		if(BlockCount[order] == BLOCK_DEPTH)
		{
			BlockPool[order] = _enlarge(order);
			BlockCount[order] = 0;
		}
		result = BlockPool[order];
		BlockPool[order] = (char*)BlockPool + BLOCK_STEP*(order + 1);
		BlockCount[order] ++;
	}
	// 若散链可用，返回散链
	result = (void*)ListPool[order];
	ListPool[order] = ListPool[order]->next;
	return result;
}
void MyMemPool::deallocate(void* p, size_t n)
{
	size_t order = n / BLOCK_STEP;
	free_list_node* temp;
	// 如果p不是nullptr
	if (p != nullptr)
	{
		// 丢给散链
		temp = (free_list_node*)p;
		p = ListPool[order];
		ListPool[order] = temp;
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
inline void* MyMemPool::_enlarge(size_t n)
{
	return (void*)malloc(sizeof(char)*BLOCK_STEP*(n+1)*BLOCK_DEPTH);
}

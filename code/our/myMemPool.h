/*
* File: myMemPool.h
* Version: 1.1
* Author: dong, kk
* Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
* Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
* -------------------------------------------
* 内存池的声明
* version 1.0: 实现内存池的基本操作，使用预先申请内存进行内存分配(dong)
* version 1.1: 改造free_list_node的类型，使用联合减少内存消耗(kk)
*/
#pragma once
#include <cstdlib>

namespace JJ
{
	#define BLOCK_STEP 8
	#define SIZE_OF_FREE_LISTS 16
	#define BLOCK_WIDTH SIZE_OF_FREE_LISTS
	#define BLOCK_DEPTH 1000
	#define TYPE_SIZE_THRESHOLD (SIZE_OF_FREE_LISTS*BLOCK_STEP)
	#define NUMBER_OF_BLOCKS_PER_STEP 20

	class MyMemPool
	{
	public:
		/*
		 * Function: MyMemPool
		 * Constructor
		 * Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
		 * Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
		 * ---------------------------------------------
		 * 构造函数在构造的时候, 同时申请内存，得到初始内存池
		 */
		MyMemPool();
		/*
		 * Function: ~MyMemPool
		 * Destructor
		 * Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
		 * Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
		 * ---------------------------------------------
		 * 析构函数，在析构的时候自动销毁释放内存池的信息
		 */
		~MyMemPool();

		/*
		 * Function: allocate
		 * Argument: n(size_t) 需要申请的内存大小
		 * Return: pointer(void *) 返回void*指针, 指向申请内存的首地址
		 * Usage: pointer = (value_type*)allocate(n);
		 * Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
		 * Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
		 * ---------------------------------------------
		 * 首先在内存池中寻找是否有可用块，有则直接类型转换返回，
		 * 没有相应的块则去申请相应的内存空间。
		 */
		void* allocate(size_t n);

		/*
		 * Function: deallocate
		 * Argument: p(void*) 需要释放的内存首地址, 但一定是一开始申请时返回的那个地址
					 n(size_t) 这个指针指向的内存块申请的大小
		 * Return: 没有返回值, 也可以后期改成bool返回值
		 * Usage: deallocate(p, n);
		 * Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
		 * Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
		 * ---------------------------------------------
		 * 采用lazy删除的方式, 将释放的内存直接拼接到内存池中。
		 */
		void deallocate(void* p, size_t n);
	private:
		union free_list_node {
			free_list_node * next;
		};
		free_list_node * ListPool[SIZE_OF_FREE_LISTS];
		void* BlockPool[BLOCK_WIDTH];
		int BlockCount[BLOCK_WIDTH];
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
		size_t _round(size_t n);

		/*
		 * Function: _enlarge
		 * Argument: n(size_t) 标准内存大小(8的倍数, 单位为Byte)
		 * Return: pointer(free_list_node*), 返回首地址
		 * Usage: free_list_node * ptr = _enlarge(_round(n)*BLOCK_STEP);
		 * Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
		 * Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
		 * ---------------------
		 * 实际去申请内存的函数，一次性申请20块作为链表返回
		 * 为了方便操作, 链表使用了头插入的方式
		 */
		inline void* _enlarge(size_t n);
	};
}

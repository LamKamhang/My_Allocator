
/*
* File: myMemPool.cpp
* Version: 1.1
* Author: dong, kk
* Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
* Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
* -------------------------------------------
* �ڴ�ص�ʵ��
* version 1.0: ʵ���ڴ�صĻ���������ʹ��Ԥ�������ڴ�����ڴ����(dong)
* version 1.1: ����free_list_node�����ͣ�ʹ�����ϼ����ڴ�����(kk)
*/
#include "myMemPool.h"

using namespace JJ;

MyMemPool::MyMemPool()
{
	for (int i = 0; i < SIZE_OF_FREE_LISTS; ++i)
		pool[i] = _enlarge((i + 1) * BLOCK_STEP);
}
/*
* Function: ~MyMemPool
* Destructor
* Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
* Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
* ---------------------------------------------
* ������������������ʱ���Զ������ͷ��ڴ�ص���Ϣ
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
	// �ҵ���Ӧ����
	size_t order = n / BLOCK_STEP;

	// ȫ����ռ����
	if (pool[order] == nullptr)
	{
		// ��������һ����ڴ�
		pool[order] = _enlarge(_round(n));
	}

	// û�п��������ڴ�ʧ�ܵ��쳣���
	free_list_node* _slot = pool[order];
	pool[order] = _slot->next;
	return (void *)_slot;
}
void MyMemPool::deallocate(void* p, size_t n)
{
	// ���p����nullptr
	if (p != nullptr)
	{
		// order�Ƕ�Ӧ�����±�, ��ͷ����ķ�ʽ����
		size_t order = n / BLOCK_STEP;
		((free_list_node *)p)->next = pool[order];
		pool[order] = (free_list_node*)p;
	}
}

/*
* Function: _round
* Argument: n(size_t) ��Ҫ������ڴ��С
* Return: _round(size_t) ��׼������ȡ���ڴ��С
* Usage: size_t normalize_n = _round(n);
* Create Date: Sun Jun 17 09:32:21 DST 2018(kk)
* ---------------------------------------------
* ��Ϊ�ڴ���еĿ��С���м����8ByteΪ��λ,(BLOCK_STEP)
* ��������Ĺ����ǽ��Ǳ�׼�Ĵ�Сround����׼��С�У�
* ����ȡ����
*/
size_t MyMemPool::_round(size_t n)
{
	/*_round����ȡ��,
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
* Argument: n(size_t) ��׼�ڴ��С(8�ı���, ��λΪByte)
* Return: pointer(free_list_node*), �����׵�ַ
* Usage: free_list_node * ptr = _enlarge(_round(n)*BLOCK_STEP);
* Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
* Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
* ---------------------
* ʵ��ȥ�����ڴ�ĺ�����һ��������20����Ϊ������
* Ϊ�˷������, ����ʹ����ͷ����ķ�ʽ
*/
MyMemPool::free_list_node* MyMemPool::_enlarge(size_t n)
{
	free_list_node *ptr, *head;
	head = ptr = nullptr;

	for (int i = 0; i < NUMBER_OF_BLOCKS_PER_STEP; ++i)
	{
		ptr = (free_list_node *)malloc(n * sizeof(char));
		ptr->next = head;
		head = ptr;
	}

	return head;
}

JJ::MyMemPool mp;
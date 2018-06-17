/*
* File: myMemPool.h
* Version: 1.1
* Author: dong, kk
* Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
* Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
* -------------------------------------------
* �ڴ�ص�����
* version 1.0: ʵ���ڴ�صĻ���������ʹ��Ԥ�������ڴ�����ڴ����(dong)
* version 1.1: ����free_list_node�����ͣ�ʹ�����ϼ����ڴ�����(kk)
*/
#pragma once
#include <cstdlib>

namespace JJ
{
	#define BLOCK_STEP 8
	#define SIZE_OF_FREE_LISTS 16
	#define TYPE_SIZE_THRESHOLD SIZE_OF_FREE_LISTS*BLOCK_STEP
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
		 * ���캯���ڹ����ʱ��, ͬʱ�����ڴ棬�õ���ʼ�ڴ��
		 */
		MyMemPool();
		/*
		 * Function: ~MyMemPool
		 * Destructor
		 * Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
		 * Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
		 * ---------------------------------------------
		 * ������������������ʱ���Զ������ͷ��ڴ�ص���Ϣ
		 */
		~MyMemPool();

		/*
		 * Function: allocate
		 * Argument: n(size_t) ��Ҫ������ڴ��С
		 * Return: pointer(void *) ����void*ָ��, ָ�������ڴ���׵�ַ
		 * Usage: pointer = (value_type*)allocate(n);
		 * Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
		 * Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
		 * ---------------------------------------------
		 * �������ڴ����Ѱ���Ƿ��п��ÿ飬����ֱ������ת�����أ�
		 * û����Ӧ�Ŀ���ȥ������Ӧ���ڴ�ռ䡣
		 */
		void* allocate(size_t n);

		/*
		 * Function: deallocate
		 * Argument: p(void*) ��Ҫ�ͷŵ��ڴ��׵�ַ, ��һ����һ��ʼ����ʱ���ص��Ǹ���ַ
					 n(size_t) ���ָ��ָ����ڴ������Ĵ�С
		 * Return: û�з���ֵ, Ҳ���Ժ��ڸĳ�bool����ֵ
		 * Usage: deallocate(p, n);
		 * Created Date: Sat Jun 16 10:41:14 DST 2018(dong)
		 * Modified Date: Sun Jun 17 09:32:21 DST 2018(kk)
		 * ---------------------------------------------
		 * ����lazyɾ���ķ�ʽ, ���ͷŵ��ڴ�ֱ��ƴ�ӵ��ڴ���С�
		 */
		void deallocate(void* p, size_t n);
	private:
		union free_list_node {
			void* block;
			free_list_node * next;
		};
		free_list_node * pool[SIZE_OF_FREE_LISTS];

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
		size_t _round(size_t n);

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
		free_list_node* _enlarge(size_t n);
	};
}

extern JJ::MyMemPool mp;
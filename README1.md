# My_Allocator
Implement an memory allocator for STL vector and list.

### 注释风格

在文件头

```c++
/*
 * File: demo.h
 * Version: 1.0
 * Author: kk
 * Create Date: Wed May 23 16:55:16 DST 2018
 * Modefied Date: Wed May 23 16:55:16 DST 2018
 * -------------------------------------------
 * 文件功能
 * 每个版本的修改的东西：
 * version 1.0 : ...
 * version 2.0 : ...
 */
```

在函数头

```c++
/*
 * Function: 函数名
 * Argument: 参数介绍
 * Return: 返回值作用
 * Usage: 如何调用该函数
 * Create Date: Wed May 23 16:55:16 DST 2018
 * Modefied Date: Wed May 23 16:55:16 DST 2018
 * --------------------
 * 函数功能的简要介绍
 * 每个版本的修改的东西：
 * version 1.0 : ...
 * version 2.0 : ...
 */

// 示例
/*
 * Function: sum
 * Argument: a(int) 第一个加数
             b(int) 第二个加数
 * Return: sum(int) 返回参数的和
 * Usage: s = sum(a, b);
 * Create Date: Wed May 23 16:55:16 DST 2018
 * Modefied Date: Wed May 23 16:55:16 DST 2018
 * ---------------------
 * 将输入参数求和，并返回结果。
 * version 1.0: 简单的实现
 */
int sum(int a, int b);
```

在函数内部

对于比较复杂的操作需要注释的话，就在那个操作上面写注释吧，不过如果注释特别短就在后面接着就好。

如果循环或者条件嵌套比较厉害，就在每个循环结束的位置加以注释标识。

```c++
for (int i = 0; i < n; ++i)
{
    for (int j = i; j < m; ++j)
    {
        if (i == j)
        {
            std::cout << "DB小组" << std::endl;
        }// end if-1
    }// end loop-2
}// end loop-1
```

------


## OOP \#Final Allocator&Mem pool

#### 文件结构

.
├── CMakeLists.txt
├── code
│   ├── our
│   │   ├── myAllocator.hpp
│   │   ├── myMemPool.cpp
│   │   ├── myMemPool.h
│   │   └── newPool.h
│   ├── testallocator.cpp
│   ├── v1
│   │   └── myallocator.h
│   └── v2
│       ├── custom_allocator.cpp
│       ├── mem_pool.cpp
│       ├── mem_pool.h
│       └── y_alloc.h
├── doc
│   └── RESULT.txt
├── README.md
├── run_our.ps1
├── run_stl.ps1
├── run_v1.ps1
├── run_v2_1.ps1
├── run_v2_2.ps1
└── test.ps1

- 所有的代码都包含在code文件夹下，包括老师之前所发工程里的三种allocator以及我们组实现的allocator。其分别在相应的文件夹下。
- 测试结果则均在doc文件夹下，都存放在RESULT.txt内。`----`区分不同的测试结果。开头的值为这若干次测试的平均值。
- 根目录下的`run_*.ps1`则是方便运行的脚本，但需要先安装`cmake`工具才可以使用。
- 根目录下的`test.ps1`则是测试100次的脚本，将输出结果存放在doc/RESULT.txt中。

#### OOP大作业要求

- 实现一个带有内存池的allocator，支持vector和list。
- 测试这个allocator的性能，利用不同的大小以及随机的值进行测试。
- allocator需要支持不同大小的allocation需求。

#### 完成情况

完成以下API

##### Allocator

```c++
// constructors and destructors
MyAllocator() noexcept;
MyAllocator(const MyAllocator& myAllocator) noexcept;
MyAllocator(MyAllocator&& myAllocator) noexcept;
template <class U>
    MyAllocator(const MyAllocator<U>& myAllocator) noexcept;
~MyAllocator() noexcept;

// operator= overload
MyAllocator& operator=(const MyAllocator& myAllocator) = delete;
MyAllocator& operator=(MyAllocator&& myAllocator) noexcept;

// get address
inline pointer address(reference _Val)  const noexcept { return &_Val; }
inline const_pointer address(const_reference _Val)const noexcept { return &_Val; }

// allocate
inline pointer allocate(size_type _Count = 1);

// deallocate
inline void deallocate(pointer _Ptr, size_type _Count = 1);

// construct
template <class _Objty, class... _Types>
        inline void construct(_Objty *_Ptr, _Types&&... _Args);

// destory
inline void destroy(pointer _Ptr);

// get max_size
size_type max_size() const noexcept;  
```

##### Memory Pool

~~~cpp
void* allocate(size_t n);
void  deallocate(void* p, size_t n);
~~~

与原来框架有所不同的是成员变量的含义：

- 这里mem pool 是allocator进行allocator的时候调用的，其相应的功能是内存管理，我们的内存池的思想是，尽可能地掌管所有的内存。所以我们在一开始的时候，先调用一大块内存，在程序进行的时候，按需分配。对于deallocate的操作，则是将返回的内存挂在free_list的红黑树上。
- 利用红黑数进行辅助的原因是，我们想尽可能地容纳所有的malloc操作，希望之前用过的内存能够在下次需要用的时候用上，所以采用红黑数的方式存储归还回来的内存。因此不采用固定长度的数组去记对应大小的内存，对超出部分free掉的方式。

#### 测试结果

- 经过若干次测试，这个内存池的在老师所给的测试文件中，基本保持在0.035s左右。
- 测试结果放在doc/RESULT.txt中

#### 如何运行

- 可以直接运行exe文件夹下的可执行文件。
- 也可以自行编译运行。
- 这里提供了5个`powershell`脚本文件，但需要在已经安装`cmake`的情况下使用。
  - run_our.ps1则是运行我们版本的allocator。
  - run_stl.ps1则是使用stl实现的标准allocator。
  - run_xww_v*.ps1则是使用老师之前所发工程内包含的三个allocator

#### 如何进行编译

###### for windows

``` powershell
cmake . -Bbuild -G"MinGW Makefiles" -DE=ON
cd build
mingw32-make
```

###### for mac/Linux

```bash
cmake . -Bbuild -DE=ON
cd build
make
```

具体的命令可以参见run_our.ps1内，用记事本打开即可。
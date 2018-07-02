/*
 * File: myAllocator.hpp
 * Version: 1.0
 * Author: kk
 * Created Date: Sat Jun 16 10:41:14 DST 2018
 * -------------------------------------------
 * 模板类Allocator的接口声明，以及模板函数实现
 */
#pragma once
#include <utility>
//#include "MyMemPool.h"
#include "newPool.h"

namespace JJ{
    
template <typename _Ty>
class MyAllocator{
public:
    // member type
    typedef     void                _Not_user_specialized;
    typedef     _Ty                 value_type;
    typedef     value_type*         pointer;
    typedef     const value_type*   const_pointer;
    typedef     value_type&         reference;
    typedef     const value_type&   const_reference;
    typedef     size_t              size_type;
    typedef     ptrdiff_t           difference_type;
    typedef std::false_type         propagate_on_container_copy_assignment;
    typedef std::true_type          propagate_on_container_move_assignment;
    typedef std::true_type          propagate_on_container_swap;

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
    inline pointer         address(reference _Val)         const noexcept    { return &_Val; }
    inline const_pointer   address(const_reference _Val)   const noexcept    { return &_Val; }

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
private:
    static MyMemPool mp;
};
template <typename _Ty> MyMemPool MyAllocator<_Ty>::mp;

// constructors and destructors
template <typename _Ty>
    MyAllocator<_Ty>::MyAllocator() noexcept
    {}
template <typename _Ty>
    MyAllocator<_Ty>::MyAllocator(const MyAllocator& myAllocator) noexcept
    {}
template <typename _Ty>
    MyAllocator<_Ty>::MyAllocator(MyAllocator&& myAllocator) noexcept
    {}
template <typename _Ty>
template <typename U>
    MyAllocator<_Ty>::MyAllocator(const MyAllocator<U>& myAllocator) noexcept
    {}
template <typename _Ty>
    MyAllocator<_Ty>::~MyAllocator() noexcept
    {}

// operator= overload
template <typename _Ty>
    MyAllocator<_Ty>& MyAllocator<_Ty>::operator=(MyAllocator&& myAllocator) noexcept
    {}

// allocate
template <typename _Ty>
    inline typename MyAllocator<_Ty>::pointer MyAllocator<_Ty>::allocate(size_type _Count)
{
    if (_Count == 0)
        return nullptr;
    auto size = sizeof(value_type) * _Count;
    return (pointer)mp.allocate(size);
}

// deallocate
template <typename _Ty>
    inline void MyAllocator<_Ty>::deallocate(pointer _Ptr, size_type _Count)
{
    auto size = sizeof(value_type) * _Count;
    mp.deallocate((void *)_Ptr, size);
}

//destroy：直接在对应地址上运行析构函数
template <typename _Ty> 
    inline void MyAllocator<_Ty>::destroy(_Ty *_Ptr)
{
    _Ptr->~value_type();
}

//construct：直接在对应地址上运行构造函数。这里是使用copy new的构造方法来实现，它不同于直接new。后者需要重新申请内存并构造，而前者只是构造。
template <typename _Ty>
template <class _Objty, class... _Types>
    inline void MyAllocator<_Ty>::construct(_Objty *_Ptr, _Types&&... _Args)
{
    new (_Ptr) _Objty(std::forward<_Types>(_Args)...);
    //new (_Ptr)  _Objty(_Args);
}

template <typename _Ty>
    inline typename MyAllocator<_Ty>::size_type MyAllocator<_Ty>::max_size() const noexcept
{
  return size_type(~0) / sizeof(_Ty);
}

}


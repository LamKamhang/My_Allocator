/*
 * File: myAllocator.hpp
 * Version: 1.0
 * Author: kk
 * Created Date: Sat Jun 16 10:41:14 DST 2018
 * -------------------------------------------
 * 模板类Allocator的接口声明，以及模板函数实现
 */
#pragma once
#include "memory_pool.h"
JJ::memory_pool mp;
namespace JJ{
    
template <typename _Ty>
class myAllocator{
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



    // constructor and destructor
    myAllocator() = default;
    myAllocator(const myAllocator&) = default;

	template<class _Other>
    myAllocator(const myAllocator<_Other>&)
    {	// construct from a related allocator (do nothing)
    }
    ~myAllocator() = default;

    inline pointer         address(reference _Val)         const     { return &_Val; }
    inline const_pointer   address(const_reference _Val)   const     { return &_Val; }

    inline void     deallocate(pointer _Ptr, size_type _Count)
    {
        size_type size = sizeof(value_type) * _Count;
        if (size > TYPE_SIZE_THRESHOLD)
        {
            free(_Ptr);
        }
        else
        {
            mp.deallocate(_Ptr, size);
        }
    }
    
    inline pointer allocate(size_type _Count)
    {
        size_type size = sizeof(value_type) * _Count;
        if (size > TYPE_SIZE_THRESHOLD)
        {
            return (pointer)malloc(size);
        }
        else
        {
            return (pointer)mp.allocate(size);
        }
    }

    template<class _Uty> 
    inline void destroy(_Uty *_Ptr)
    {
        _Ptr->~value_type();
    }

    template<class _Objty, class _Types>
    inline void construct(_Objty *_Ptr, _Types& _Arg)
    {
        new (_Ptr) _Objty(_Arg);
    }
};

}



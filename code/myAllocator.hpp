/*
 * File: myAllocator.hpp
 * Version: 1.0
 * Author: kk
 * Created Date: Sat Jun 16 10:41:14 DST 2018
 * -------------------------------------------
 * 模板类Allocator的接口声明，以及模板函数实现
 */

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
    typedef     true_type           propagate_on_container_move_assignment;
    typedef     true_type           is_always_equal;

    // constructor and destructor
    myAllocator() _NOEXCEPT = default;
    myAllocator(const allocator&) _NOEXCEPT = default;

	template<class _Other>
    myAllocator(const allocator<_Other>&) _NOEXCEPT
    {	// construct from a related allocator (do nothing)
    }
    ~myAllocator() _NOEXCEPT = default;


    pointer         address(reference _Val)         const _NOEXCEPT     { return &_Val; }
    const_pointer   address(const_reference _Val)   const _NOEXCEPT     { return &_Val; }
    void            deallocate(pointer _Ptr, size_type _Count);
    _DECLSPEC_ALLOCATOR pointer allocate(size_type _Count);
    template<class _Uty> void destroy(_Uty *_Ptr);
    template<class _Objty,
            class... _Types>
    void            construct(_Objty *_Ptr, _Types&&... _Args);
};

}

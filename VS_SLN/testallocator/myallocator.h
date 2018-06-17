#ifndef MY_ALLOCATOR_H
#define MY_ALLOCATOR_H
#include <cstddef>
#include <type_traits>
#include <climits>
#include <utility>
#include <stdexcept>

const size_t BlockSize = 4096;
template <typename T>
class MyAllocator
{
public:
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef const T* const_pointer;
  typedef const T& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef std::false_type propagate_on_container_copy_assignment;
  typedef std::true_type propagate_on_container_move_assignment;
  typedef std::true_type  propagate_on_container_swap;
  template <typename U> struct rebind
  {
    typedef MyAllocator<U> Other;
  };
  MyAllocator() noexcept;
  MyAllocator(const MyAllocator& myallocator) noexcept;
  MyAllocator(MyAllocator&& myallocator) noexcept;
  template <class U>MyAllocator(const MyAllocator<U>& myallocator) noexcept;
  ~MyAllocator() noexcept;
  MyAllocator& operator=(const MyAllocator& myallocator) = delete;
  MyAllocator& operator=(MyAllocator&& myallocator) noexcept;
  pointer address(reference x) const noexcept;
  const_pointer address(const_reference x) const noexcept;
  pointer allocate(size_type n = 1, const_pointer hint = 0);
  void deallocate(pointer p, size_type n = 1);
  size_type max_size() const noexcept;
  template <class U, class... Args> void construct(U* p, Args&&... args);
  void destroy(pointer p);
private:
  struct Block_ {
    Block_ *next;
  };
  typedef Block_* blockpointer;
  static inline blockpointer freeBlocks_ = nullptr;
  static_assert(BlockSize >= 2 * sizeof(T), "Blocksize too small.");
};
template<typename T>
MyAllocator<T>::MyAllocator() noexcept
{}
template<typename T>
MyAllocator<T>::MyAllocator(const MyAllocator & myallocator) noexcept :MyAllocator()
{}
template<typename T>
MyAllocator<T>::MyAllocator(MyAllocator && myallocator) noexcept
{}
template<typename T>
template <class U>
MyAllocator<T>::MyAllocator(const MyAllocator<U>& myallocator) noexcept :MyAllocator()
{}
template<typename T>
MyAllocator<T> & MyAllocator<T>::operator=(MyAllocator && myallocator) noexcept
{}
template<typename T>
MyAllocator<T>::~MyAllocator() noexcept
{}
template<typename T>
inline typename MyAllocator<T>::pointer MyAllocator<T>::address(reference x) const noexcept
{
  return &x;
}
template <typename T>
inline typename MyAllocator<T>::const_pointer MyAllocator<T>::address(const_reference x) const noexcept
{
  return &x;
}
template<typename T>
inline typename MyAllocator<T>::pointer MyAllocator<T>::allocate(size_type n, const_pointer hint)
{
  if (n > max_size())
    throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");

  pointer p = nullptr;
  if (n * sizeof(T) > BlockSize)
  {
    p = reinterpret_cast<pointer>(operator new(n * sizeof(T)));
  }
  else
  {
    if (freeBlocks_ != nullptr)
    {
      p = reinterpret_cast<pointer>(freeBlocks_);
      freeBlocks_ = freeBlocks_->next;
    }
    else
    {
      p = reinterpret_cast<pointer>(operator new(BlockSize));
    }
  }
  return p;
}
template<typename T>
inline void MyAllocator<T>::deallocate(pointer p, size_type n)
{
  if (p != nullptr)
  {
    blockpointer newBlock_ = reinterpret_cast<blockpointer>(p);
    newBlock_->next = freeBlocks_;
    freeBlocks_ = newBlock_;
  }
}
template<typename T>
inline typename MyAllocator<T>::size_type MyAllocator<T>::max_size() const noexcept
{
  return size_type(~0) / sizeof(T);
}
template<typename T>
template<class U, class... Args>
inline void MyAllocator<T>::construct(U* p, Args&&... args)
{
  new (p) U(std::forward<Args>(args)...);
}
template<typename T>
inline void MyAllocator<T>::destroy(pointer p)
{
  p->~T();
}

#endif // !MY_ALLOCATOR_H
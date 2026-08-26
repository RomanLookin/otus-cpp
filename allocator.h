#ifndef ALLOCATOR_HEADER
#define ALLOCATOR_HEADER
 
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <limits>

 


long long factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1); // Ресивный шаг
}

template<typename T>
class LoggingAllocator {
public:
    using value_type = T;

    T* allocate(size_t n) {
        std::cout << "Alloc n=" << std::to_string(n) << " elements" << std::endl;
        if(n > 20){
            throw std::runtime_error("more than 10 items requested");
        }
        T* pt = static_cast<T*>(::operator new(n * sizeof(T)));
        if(pt == nullptr)
            throw std::bad_alloc();
        std::cout << "Alloc n=" << std::to_string(n) << " size =" << n * sizeof(T) << " bytes." << "adress " << pt << std::endl;
        return pt;
    }

    void deallocate(T* p, size_t n) {
        std::cout << "Dealloc " << n * sizeof(T) << " bytes" << std::endl;
        ::operator delete(p);
    }

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) {

        U* pt = new(p) U(std::forward<Args>(args)...);
        if(pt == nullptr)
          throw std::bad_alloc();
        std::cout << "ctor." << "adr " << pt << std::endl;
    }

    template<typename U>
    void destroy(U* p) noexcept {
        std::cout << "dtor adr " << p << std::endl;
        p->~U();
    }

    template<typename U>
    size_t max_size() const noexcept
    {
        return std::numeric_limits<size_t>::max() / sizeof(U);
    }
};


template <typename T, typename Allocator = std::allocator<T>>
class MyVector {
public:
    // Типы
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = value_type*;
    using const_iterator = const value_type*;
    using size_type = size_t;
    using AllocTraits = std::allocator_traits<Allocator>;

    // Конструкторы
    MyVector() : data_(nullptr), size_(0), capacity_(0) {}
    MyVector(size_type n) : data_(nullptr), size_(0), capacity_(0) {
      if (n > 0) {
        data_ = allocator_.allocate(n);
        for (size_type i = 0; i < n; ++i) {
          AllocTraits::construct(allocator_, data_ + i);
        }
      }
      size_ = capacity_ = n;
    }

    void clear() {
      if (size_ != 0) {
        for (size_type i = 0; i < size_; ++i) {
          AllocTraits::destroy(allocator_, data_ + i);
        }
        size_ = 0;
      }
    }

    ~MyVector() {
      clear();
      if (data_) allocator_.deallocate(data_, capacity_);
      data_ = nullptr;
      size_ = capacity_ = 0;
    }

    T* data() {
      return data_;
    }

    iterator begin() {
      return iterator(data_);
    }

    iterator end() {
      return iterator(data_ + size_);
    }

    bool empty() {
      return (size_ == 0);
    }

    size_type size() {
      return size_;
    }

    size_type max_size() {
      return AllocTraits::max_size(allocator_);
    }

    void reserve(size_type size) {
      if (size > max_size()) {
        throw std::length_error("reserve: new capacity exceeds max_size()");
      } else if (size > capacity_) {
        iterator new_data = allocator_.allocate(size);
        for (size_type i = 0; i < size_; ++i) {
          AllocTraits::construct(allocator_, new_data + i,
                                 std::move_if_noexcept(data_[i]));
        }
        for (size_type i = 0; i < size_; ++i) {
          AllocTraits::destroy(allocator_, data_ + i);
        }
        allocator_.deallocate(data_, capacity_);
        data_ = new_data;
        capacity_ = size;
      }
    }

    size_type capacity() {
      return capacity_;
    }

    void push_back(const_reference value) {
      if (size_ == capacity_) {
        size_type new_cap = capacity_ ? capacity_ * 2 : 1;
        reserve(new_cap);
      }
      AllocTraits::construct(allocator_, data_ + size_, value);
      ++size_;
    }


private:

    iterator data_;
    size_type size_;
    size_type capacity_;
    //std::allocator<T> allocator_;
    Allocator  allocator_;
};
#endif // ALLOCATOR_HEADER

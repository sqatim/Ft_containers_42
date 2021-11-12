#ifndef VECTOR_CLASS_HPP
#define VECTOR_CLASS_HPP

// The explicit keyword in C++ is used to mark constructors to not implicitly convert types.
#include <iostream>

// template<typename T>
// class Allocator
// {
// public:
//     template<class Type>
//     struct rebind
//     {
//         typedef Allocator<Type> other;
//     };
//     typedef T value_type;
//     typedef T* pointer;
//     typedef T& reference;
//     typedef const T* const_pointer;
//     typedef const T& const_reference;
//     typedef size_t size_type;
//     typedef std::ptrdiff_t difference_type;

// public:
//     Allocator();
//     ~Allocator();
//     pointer address(reference x) const;
//     const pointer address(const reference x) const;
//     pointer allocate(size_type n, Allocator<void>::const_pointer hint=0);
//     void deallocate(pointer p, size_type n);
//     size_type max_size() const throw();
//     void construct(pointer p, const_reference val);
//     void destroy(pointer p);
// private:

// };

template <class T, class Alloc = std::allocator<T> >
class Vector
{
public:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef size_t size_type;

public:
    T *m_data;
    allocator_type m_allocator;
    size_type m_capacity;
    size_type m_size;


public:
    // Constructs:

    //Construit l'allocateur par défaut. Étant donné que l'allocateur par défaut est sans état, les constructeurs n'ont aucun effet visible.
    explicit Vector(const allocator_type &alloc = allocator_type()) : m_capacity(0), m_size(0)
    {
        m_allocator = const_cast<allocator_type &>(alloc);
        m_data = m_allocator.allocate(0);
    };

    explicit Vector(size_type n, const value_type &val = value_type(),
                    const allocator_type &alloc = allocator_type()) : m_capacity(n), m_size(n)
    {
        m_allocator = const_cast<allocator_type &>(alloc);
        m_data = m_allocator.allocate(n);
        for (int i = 0; i < n; i++)
        {
            m_data[i] = val;
        }
    };

    // template <class InputIterator>
    // Vector(InputIterator first, InputIterator last,
    //        const allocator_type &alloc = allocator_type()){

    //        };

    Vector(const Vector &x)
    {
        *this = x;
        return;
    };

    // Capacity:
    size_type size() const {return (m_size);};
    size_type max_size() const;
    void resize(size_type n, value_type val = value_type());
    size_type capacity() const;
    bool empty() const;
    void reserve(size_type n);

    // Element access:
    reference operator[](size_type n)
    {
        return m_data[n];
    };
    const_reference operator[](size_type n) const{return m_data[n];};

    reference at(size_type n)
    {
        // hta n9ad liha exception dyal man ba3d fash katfout size dyal vector;
        return (m_data[n]);
    };
    const_reference at(size_type n) const
    {
        // hta n9ad liha exception dyal man ba3d fash katfout size dyal vector;
        return (m_data[n]);
    };

    reference front() {return (m_data[0]);};
    const_reference front() const {return (m_data[0]);};

    reference back();
    const_reference back() const;

    // Modifiers;
    void clear()
    {
        for(size_type i = 0; i < m_size; i++)
            m_data[i].~T();
        m_size = 0;
    };

    // iterator insert( iterator pos, const T& value );
    // void insert( iterator pos, size_type count, const T& value );
    // template< class InputIt >
    // void insert( iterator pos, InputIt first, InputIt last );

    // iterator erase( iterator pos );
    // iterator erase( iterator first, iterator last );

    // void push_back( const T& value );

    // void pop_back();

    // void resize( size_type count, T value = T() );

    void swap( Vector& other )
    {
        Vector tmp;
        
        tmp = *this;
        *this = other;
        other = tmp;
    }

    ~Vector(){};
};

#endif
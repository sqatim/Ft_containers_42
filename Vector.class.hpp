#ifndef VECTOR_CLASS_HPP
#define VECTOR_CLASS_HPP

// The explicit keyword in C++ is used to mark constructors to not implicitly convert types.
#include <iostream>
#include "NormalIterator.class.hpp"

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
    typedef Normal_iterator<T> iterator;

private:
    T *m_data;
    allocator_type m_allocator;
    size_type m_capacity;
    size_type m_size;
    void allocateAndCopy(size_type n)
    {
        T *tmp = m_allocator.alloc(n);
        for (size_type i = 0; i < m_size; i++)
        {
            tmp[i] = m_data[i];
        }
        m_allocator.deallocate(m_data, m_capacity);
        m_data = tmp;
        m_capacity = n;
    };

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
    size_type size() const { return (m_size); };
    size_type max_size() const { return m_allocator.max_size(); };
    size_type capacity() const { return (m_capacity); };
    bool empty() const
    {
        if (m_size == 0)
            return (true);
        return false;
    };

    void reserve(size_type n)
    {
        // If the size requested is greater than the maximum size (vector::max_size), a length_error exception is thrown.
        if (n > m_capacity)
        {
            this->allocateAndCopy(n);
        }
    };

    // Element access:
    reference operator[](size_type n)
    {
        return m_data[n];
    };
    const_reference operator[](size_type n) const { return m_data[n]; };

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

    reference front() { return (m_data[0]); };
    const_reference front() const { return (m_data[0]); };

    reference back() { return (m_data[m_size - 1]); };
    const_reference back() const { return (m_data[m_size - 1]); };

    // Modifiers;
    void clear()
    {
        for (size_type i = 0; i < m_size; i++)
            m_data[i].~T();
        m_size = 0;
    };

    // iterator insert( iterator pos, const T& value );
    // void insert( iterator pos, size_type count, const T& value );
    // template< class InputIt >
    // void insert( iterator pos, InputIt first, InputIt last );

    // iterator erase( iterator pos );
    // iterator erase( iterator first, iterator last );

    void push_back(const T &value)
    {
        if (m_size >= m_capacity)
            this->allocateAndCopy(m_capacity * 2);
        m_data[m_size++] = value;
    };

    void pop_back()
    {
        m_data[m_size - 1].~T();
        m_size--;
    }

    void resize(size_type count, T value = T())
    {
        // If a reallocation happens, the storage is allocated using the container's allocator, which may throw exceptions on failure (for the default allocator, bad_alloc is thrown if the allocation request does not succeed).
        if (count <= m_size - 1)
        {
            for (size_type i = m_size - 1; i >= count; i--)
            {
                m_data[i].~T();
                m_size--;
            }
        }
        else
        {
            if(count > m_capacity)
                this->allocateAndCopy(count);
            for(size_type i = m_size; i < count; i++)
            {
                m_data[i++] = value;
            }
        }
    };

    void swap(Vector &other)
    {
        Vector tmp;

        tmp = *this;
        *this = other;
        other = tmp;
    }

    ~Vector(){};
};

#endif
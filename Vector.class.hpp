#ifndef VECTOR_CLASS_HPP
#define VECTOR_CLASS_HPP

// The explicit keyword in C++ is used to mark constructors to not implicitly convert types.
#include <iostream>
#include "NormalIterator.class.hpp"
#include "ReverseIterator.class.hpp"
#include <cstddef>

template <class T, class Alloc = std::allocator<T>>
class Vector
{
public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef size_t size_type;
	typedef Normal_iterator<pointer> iterator;
	typedef Normal_iterator<const_pointer> const_iterator;
	typedef Reverse_iterator<pointer> reverse_iterator;
	typedef const Reverse_iterator<const_pointer> const_reverse_iterator;

private:
	T *m_data;
	allocator_type m_allocator;
	size_type m_capacity;
	size_type m_size;

	void allocateAndCopy(size_type n, size_type size)
	{
		T *tmp;

		tmp = m_allocator.allocate(n);
		for (size_type i = 0; i < size; i++)
		{
			tmp[i] = m_data[i];
		}
		if (m_capacity > 0)
			m_allocator.deallocate(m_data, m_capacity);
		m_data = tmp;
		m_capacity = n;
	};

public:
	// Constructs:

	//Construit l'allocateur par défaut. Étant donné que l'allocateur par défaut est sans état, les constructeurs n'ont aucun effet visible.
	explicit Vector(const allocator_type &alloc = allocator_type()) : m_data(NULL), m_capacity(0), m_size(0), m_allocator(alloc){};

	explicit Vector(size_type n, const value_type &val = value_type(),
					const allocator_type &alloc = allocator_type()) : m_capacity(n), m_size(n), m_allocator(alloc)
	{
		// m_allocator = const_cast<allocator_type &>(alloc);
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
			this->allocateAndCopy(n, m_size);
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
		if (n < m_size)
			return (m_data[n]);
		else
			throw std::out_of_range("vector::_M_range_check: __n (which is " + std::to_string(n) + ") >= this->size() (which is " + std::to_string(this->m_size) + ")");
	};
	const_reference at(size_type n) const
	{
		if (n < m_size)
			return (m_data[n]);
		else
			throw std::out_of_range("vector::_M_range_check: __n (which is " + std::to_string(n) + ") >= this->size() (which is " + std::to_string(this->m_size) + ")");
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

	void insertAllocation(size_type capacity, std::ptrdiff_t len, const T &value, const size_type &count)
	{
		T *tmp;
		size_type j;

		j = 0;
		tmp = m_allocator.allocate(capacity);
		for (int k = 0; j < m_size + count; j++)
		{
			if (len == j)
				for (int counter = 0; counter < count; counter++)
					tmp[j++] = value;
			tmp[j] = m_data[k++];
		}
		m_allocator.deallocate(m_data, m_capacity);
		m_data = tmp;
		m_capacity = capacity;
		m_size += count;
	}

	iterator insert(iterator pos, const T &value)
	{
		// hna ma khasnish nfout end ! akhir element n9dar nzid momkin ikun fal end
		std::ptrdiff_t len;
		T *tmp;
		size_type k;

		len = pos.base() - this->begin().base();
		if (len <= (std::ptrdiff_t)m_size && m_size < m_capacity)
		{
			for (k = m_size; (std::ptrdiff_t)k > len; k--)
				m_data[k] = m_data[k - 1];
			m_data[k] = value;
			m_size++;
		}
		else if (len <= m_size && m_size >= m_capacity)
			insertAllocation(m_capacity * 2, len, value, 1);
		return this->begin() + len;
	};

	void insert(iterator pos, size_type count, const T &value)
	{
		size_type k;
		size_type i;
		size_type capacity;
		std::ptrdiff_t len;

		len = pos.base() - this->begin().base();
		i = 1;
		if (count < 0)
			throw("vector::_M_fill_insert");
		else if (count == 0)
			return;
		else if (len <= (std::ptrdiff_t)m_size && m_size + count <= m_capacity)
		{
			for (k = m_size + count - 1; (std::ptrdiff_t)k > len + count - 1; k--)
			{
				m_data[k] = m_data[m_size - i];
				i++;
			}
			for (int i = 0; i < count; i++)
				m_data[k--] = value;
			m_size += count;
		}
		else if (len <= m_size && m_size + count > m_capacity)
		{
			capacity = (m_size + count <= m_capacity * 2) ? m_capacity * 2 : m_size + count;
			insertAllocation(capacity, len, value, count);
		}
		else
			throw std::string("out of range");
	};

	template <class InputIt>
	void insertAllocationGeneric(std::ptrdiff_t len, InputIt first, InputIt last)
	{
		T *tmp;
		size_type j;
		std::ptrdiff_t count;
		size_type capacity;

		j = 0;
		count = last - first;
		capacity = (m_size + count != m_capacity + 1 && m_size + count <= m_capacity * 2) ? m_capacity * 2 : m_size + count;
		tmp = m_allocator.allocate(capacity);
		for (int k = 0; j < m_size + count; j++)
		{
			if (len == j)
				for (; first < last; first++)
					tmp[j++] = *first;
			tmp[j] = m_data[k++];
		}
		m_allocator.deallocate(m_data, m_capacity);
		m_data = tmp;
		m_capacity = capacity;
		m_size += count;
	}

	template <class InputIt>
	void insert(iterator pos, InputIt first, InputIt last)
	{
		size_type i;
		size_type k;
		std::ptrdiff_t len;
		std::ptrdiff_t count;

		if (first > last)
			throw std::string("vector::_M_range_insert");
		else if (first == last)
			return;
		len = pos.base() - this->begin().base();
		count = last - first;
		if (len <= (std::ptrdiff_t)m_size && m_size + count <= m_capacity)
		{
			i = 1;
			for (k = m_size + count - 1; (std::ptrdiff_t)k > len + count - 1; k--, i++)
				m_data[k] = m_data[m_size - i];
			for (int i = 0; i < count; i++, first++)
				m_data[k--] = *first;
			m_size += count;
		}
		else if (len <= m_size && m_size + count > m_capacity)
			insertAllocationGeneric(len, first, last);
	};

	template <class InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		//   v1.assign(3, 100); nnormalement hadi khasha dkhul fal function lakhra
		T *tmp;
		size_type counter;

		if (first < last)
		{
			this->clear();
			counter = 0;
			for (InputIterator tmp = first; tmp < last; tmp++)
				counter++;
			if (m_capacity < counter)
			{
				tmp = m_allocator.allocate(counter);
				for (int i = 0; i < counter; first++)
					tmp[i++] = *first;
				if (m_capacity > 0)
					m_allocator.deallocate(m_data, m_capacity);
				m_data = tmp;
				m_capacity = counter;
			}
			else
				for (int i = 0; i < counter; first++)
					m_data[i++] = *first;
			m_size = counter;
		}
	}

	void assign(size_type n, const value_type &val)
	{
		T *tmp;
		size_t i;

		i = 0;
		this->clear();
		if (m_capacity < n)
		{
			if (n > 0)
			{
				tmp = m_allocator.allocate(n);
				while (i < n)
					tmp[i++] = val;
				if (m_capacity > 0)
					m_allocator.deallocate(m_data, m_capacity);
				m_data = tmp;
				m_capacity = n;
			}
		}
		else
			while (i < n)
				m_data[i++] = val;
		m_size = n;
	}

	iterator erase(iterator pos)
	{
		iterator begin = this->begin();
		bool check = false;
		size_type i = 0;
		size_type j = 0;

		for (; begin < this->end(); begin++)
		{
			if (begin == pos)
			{
				check = true;
				break;
			}
			i++;
		}
		if (check == false && this->begin() == pos)
			check = true;
		if (check == true)
		{
			begin = this->begin();
			if (m_size == 1)
				this->clear();
			else
			{
				j = 0;
				for (int k = 0; k < m_size; begin++)
				{
					if (begin == pos)
						k++;
					m_data[j++] = m_data[k++];
				}
				m_size--;
			}
		}
		return begin;
	}

	iterator erase(iterator first, iterator last)
	{
		size_type j = 0;
		size_type i = 0;
		iterator tmp;
		if (first < this->begin() || last > this->end())
			std::cout << "alla aa sahbu" << std::endl;
		else
		{
			tmp = first;
			for (; tmp < last; tmp++)
				i++;
			j = 0;
			for (int k = 0; k < m_size; first++)
			{
				tmp = this->begin();
				if (tmp == first)
					k += i;
				m_data[j++] = m_data[k++];
			}
			m_size -= i;
		}
		return (first);
	};

	void push_back(const T &value)
	{
		if (m_capacity == 0)
			this->allocateAndCopy(1, m_size);
		if (m_size >= m_capacity)
			this->allocateAndCopy(m_capacity * 2, m_size);
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
		if (count <= m_size)
		{
			for (int i = (int)m_size; i >= (int)count; i--)
				m_data[i].~T();
			m_size = count;
		}
		else
		{
			if (count > m_capacity)
				this->allocateAndCopy(count, m_size);
			for (size_type i = m_size; i < count; i++)
				m_data[i] = value;
			m_size = count;
		}
	};

	void swap(Vector &other)
	{
		Vector tmp;

		tmp = *this;
		*this = other;
		other = tmp;
	}

	// Iterators
	iterator begin() { return iterator(m_data); };
	const_iterator begin() const { return iterator(m_data); };

	iterator end() { return iterator(m_data + m_size); }
	const_iterator end() const { return const_iterator(m_data + m_size); }

	reverse_iterator rbegin() { return (reverse_iterator(m_data + m_size)); };
	const_reverse_iterator rbegin() const
	{
		std::cout << "rbegin" << std::endl;
		return (reverse_iterator(m_data + m_size));
	};

	reverse_iterator rend() { return reverse_iterator(m_data); };
	const_reverse_iterator rend() const { return reverse_iterator(m_data); };

	allocator_type get_allocator() const { return (this->m_allocator); };
	// const_itera
	~Vector()
	{
		if (m_capacity > 0)
			m_allocator.deallocate(m_data, m_capacity);
	};
};

#endif

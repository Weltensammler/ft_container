/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:32:44 by jbartkow          #+#    #+#             */
/*   Updated: 2023/03/02 13:34:29 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>
#include "iterator.hpp"

namespace ft
{

	template <	typename T,
				typename Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T													value_type;
		typedef Allocator											allocator_type;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename ft::Iterator<T>							iterator;
		typedef typename ft::Iterator<const T>						const_iterator;
		typedef typename ft::reverse_Iterator<iterator>				reverse_iterator;
		typedef typename ft::reverse_Iterator<const_iterator>		const_reverse_iterator;
		typedef typename allocator_type::size_type					size_type;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;

	private:

		allocator_type	_alloc;
		pointer			_container;
		pointer			_end;
		size_type		_capacity;

	public:

		/* Default constructor */
		explicit vector(const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _container(NULL), _end(NULL), _capacity(0) {}

		/* Fill constructor */
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _container(NULL), _end(NULL), _capacity(0)
		{
			if (n > this->max_size())
				throw std::length_error("vector::fill_constructor");
			if (n > 0)
				this->_container = _alloc.allocate(n);
			this->_capacity = n;
			this->_end = this->_container;
			while (n--)
			{
				_alloc.construct(this->_end, val);
				this->_end++;
			}
		}

		/* Range constructor */
		/* enable_if is needed because range constructor is a better match then fill constructor (for example two numbers)*/
		template<class InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type &alloc = allocator_type(),
				typename enable_if<!is_integral<InputIterator>::value>::type* = NULL) : _alloc(alloc)
		{
			this->_alloc = alloc;
			this->_capacity = 1;
			this->_container = _alloc.allocate(1);
			this->_end = this->_container;
			while (first != last)
			{
				this->push_back(*first);
				first++;
			}
		}

		/* Copy Constructor */
		vector(const vector &rhs) : _alloc(rhs._alloc), _container(NULL), _end(NULL), _capacity(0)
		{
			this->insert(this->begin(), rhs.begin(), rhs.end());
		}

		/* Deconstructor */
		~vector()
		{
			this->clear();
			if (this->capacity() != 0)
				this->_alloc.deallocate(this->_container, this->capacity());
		}

		/* Assignment operator */
		vector &operator=(const vector &rhs)
		{
			if (rhs == *this)
				return (*this);
			if (this->size() > 0)
				this->clear();
			this->insert(this->end(), rhs.begin(), rhs.end());
			return (*this);
		}

		iterator begin(void)
		{
			return (iterator(this->_container));
		}

		const_iterator begin(void) const
		{
			return (const_iterator(this->_container));
		}

		iterator end(void)
		{
			if (this->empty())
				return (this->begin());
			return (iterator(this->_end));
		}

		const_iterator end(void) const
		{
			if (this->empty())
				return (this->begin());
			return (const_iterator(this->_end));
		}

		reverse_iterator rbegin(void)
		{
			return (reverse_iterator(this->_end));
		}

		const_reverse_iterator rbegin(void) const
		{
			return (reverse_iterator(this->_end));
		}

		reverse_iterator rend(void)
		{
			return (reverse_iterator(this->_container));
		}

		const_reverse_iterator rend(void) const
		{
			return (reverse_iterator(this->_container));
		}

		size_type size(void) const
		{
			return (this->_end - this->_container);
		}

		size_type max_size(void) const
		{
			return (allocator_type().max_size());
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n > this->max_size())
				throw std::length_error("vector::resize");
			else if (n < this->size())
			{
				while (this->size() > n)
				{
					this->_end--;
					this->_alloc.destroy(this->_end);
				}
			}
			else
				this->insert(this->end(), n - this->size(), val);
		}

		size_type capacity(void) const
		{
			return (this->_capacity);
		}

		bool empty(void) const
		{
			if (this->size() == 0)
				return (true);
			return (false);
		}

		void reserve(size_type n)
		{
			if (n > this->max_size())
				throw std::length_error("vector::reserve");
			else if (n > this->capacity())
			{
				pointer prev_start = this->_container;
				pointer prev_end = this->_end;
				size_type prev_size = this->size();
				size_type prev_capacity = this->capacity();

				this->_container = this->_alloc.allocate(n);
				this->_capacity = n;
				this->_end = this->_container;
				while (prev_start != prev_end)
				{
					this->_alloc.construct(this->_end, *prev_start);
					this->_end++;
					prev_start++;
				}
				prev_start = prev_start - prev_size;
				while (prev_start != prev_end)
				{
					_alloc.destroy(prev_start);
					prev_start++;
				}
				if (prev_start)
					this->_alloc.deallocate(prev_start - prev_size, prev_capacity);
			}
		}

		reference operator[](size_type n)
		{
			return (*(this->_container + n));
		}

		const_reference operator[](size_type n) const
		{
			return (*(this->_container + n));
		}

		reference at(size_type n)
		{
			if (n >= this->size())
				throw std::out_of_range("Out of Range");
			return ((*this)[n]);
		}

		const_reference at(size_type n) const
		{
			if (n >= this->size())
				throw std::out_of_range("Out of Range");
			return ((*this)[n]);
		}

		reference front(void)
		{
			return (*this->_container);
		}

		const_reference front(void) const
		{
			return (*this->_container);
		}

		reference back(void)
		{
			return (*(this->_end - 1));
		}

		const_reference back(void) const
		{
			return (*(this->_end - 1));
		}

		template<class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename enable_if<!is_integral<InputIterator>::value>::type* = NULL,
					typename enable_if<!is_same<typename iterator_traits<InputIterator>::iterator_category, std::input_iterator_tag>::value>::type* = NULL)
		{
			this->clear();
			size_type dist = ft::distance(first, last);
			if (_capacity >= dist)
			{
				while (first != last)
				{
					this->_alloc.construct(this->_end, *first);
					first++;
					this->_end++;
				}
			}
			else
			{
				pointer new_start = this->_alloc.allocate(dist);
				pointer new_end = new_start;
				size_type new_capacity = dist;
				while (first != last)
				{
					this->_alloc.construct(new_end, *first);
					first++;
					new_end++;
				}
				if (this->_container)
					this->_alloc.deallocate(this->_container, this->capacity());
				this->_container = new_start;
				this->_end = new_end;
				this->_capacity = new_capacity;
			}
		}

		template<class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename enable_if<!is_integral<InputIterator>::value>::type* = NULL,
					typename enable_if<is_same<typename iterator_traits<InputIterator>::iterator_category, std::input_iterator_tag>::value>::type* = NULL)
		{
			this->clear();
			pointer tmp_container = this->_container;
			this->_container = this->_alloc.allocate(1);
			this->_end = this->_container;
			size_type tmp_capacity = this->_capacity;
			this->_capacity = 1;
			while (first != last)
			{
				this->push_back(*first);
				first++;
			}
			if (tmp_container)
				this->_alloc.deallocate(tmp_container, tmp_capacity);
		}

		void assign(size_type n, const value_type &val)
		{
			this->clear();
			if (n == 0)
				return ;
			if (this->_capacity >= n)
			{
				while (n)
				{
					this->_alloc.construct(this->_end, val);
					n--;
					this->_end++;
				}
			}
			else
			{
				if (this->_container)
					this->_alloc.deallocate(this->_container, this->capacity());
				this->_container = this->_alloc.allocate(n);
				this->_end = this->_container;
				this->_capacity = n;
				while (n)
				{
					this->_alloc.construct(this->_end, val);
					n--;
					this->_end++;
				}
			}
		}

		void push_back(const value_type &val)
		{
			if (this->size() == this->_capacity)
			{
				int new_capacity;
				if (this->size() == 0)
					new_capacity = 1;
				else
					new_capacity = this->capacity() * 2;
				this->reserve(new_capacity);
			}
			this->_alloc.construct(this->_end, val);
			this->_end++;
		}

		void pop_back(void)
		{
			this->_alloc.destroy(&(this->back()));
			this->_end--;
		}

		iterator insert(iterator position, const value_type &val)
		{
			size_type pos = &(*position) - this->_container;
			if (this->_capacity - size() >= this->size() + 1)
			{
				for (size_type i = 0; i < pos; i++)
					this->_alloc.construct(this->_end - i, *(this->_end - i - 1));
				this->_end++;
				this->_alloc.construct(&(*position), val);
			}
			else
			{
				int new_capacity;
				if (this->size() == 0)
					new_capacity = 1;
				else if (this->size() >= this->capacity())
					new_capacity = this->capacity() * 2;
				else
					new_capacity = capacity();
				pointer new_start = this->_alloc.allocate(new_capacity);
				pointer new_end = new_start + this->size() + 1;
				for (size_type i = 0; i < pos; i++)
					this->_alloc.construct(new_start + i, *(this->_container + i));
				this->_alloc.construct(new_start + pos, val);
				for (size_type j = 0; j < this->size() - pos; j++)
					this->_alloc.construct(new_end - j - 1, *(this->_end - j - 1));
				for (size_type k = 0; k < this->size(); k++)
					this->_alloc.destroy(this->_container + k);
				if (this->_container)
					this->_alloc.deallocate(this->_container, this->capacity());
				this->_container = new_start;
				this->_end = new_end;
				this->_capacity = new_capacity;
			}
			return (iterator(this->_container + pos));
		}

		/*Fill Insert*/
		void insert(iterator position, size_type n, const value_type &val)
		{
			if (n == 0)
				return ;
			if (n > this->max_size())
				throw std::length_error("vector::insert");
			size_type pos = &(*position) - this->_container;
			if (this->_capacity >= n + this->size())
			{
				for (size_type i = 0; i < n; i++)
				{
					this->_alloc.construct(this->_end + i, val);
				}
				for (size_type i = 0; i < this->size() - pos; i++)
				{
						this->_container[this->size() - i + (n - 1)] = *(this->_end - i - 1);
				}
				this->_end += n;
				while (n)
				{
					this->_container[pos + (n - 1)] = val;
					n--;
				}
			}
			else
			{
				size_type new_capacity;
				if (this->size() == 0)
					new_capacity = n;
				else
					new_capacity = size() + n;
				pointer new_start = this->_alloc.allocate(new_capacity);
				pointer new_end = pointer();
				if (new_capacity < this->size() + n)
				{
					if (new_start)
						this->_alloc.deallocate(new_start, new_capacity);
					new_capacity = this->size() + n;
					new_start = this->_alloc.allocate(new_capacity);
				}
				new_end = new_start + this->size() + n;
				for (int i = 0; i < (&(*position) - this->_container); i++)
					this->_alloc.construct(new_start + i, *(this->_container + i));
				for (size_type j = 0; j < n; j++)
					this->_alloc.construct(new_start + pos + j, val);
				for (size_type k = 0; k < (this->size() - pos); k++)
					this->_alloc.construct(new_end - k - 1, *(this->_end - k - 1));
				for (size_type l = 0; l < this->size(); l++)
					this->_alloc.destroy(this->_container + l);
				if (this->_container)
					this->_alloc.deallocate(this->_container, this->capacity());
				this->_container = new_start;
				this->_end = new_end;
				this->_capacity = new_capacity;
			}
		}

		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename enable_if<!is_integral<InputIterator>::value>::type* = NULL,
					typename enable_if<is_same<typename iterator_traits<InputIterator>::iterator_category, std::input_iterator_tag>::value>::type* = NULL)
		{
			vector<T> temp1;
			vector<T> temp2;
			size_type i = 0;
			size_type k = 0;
			size_type pos = &(*position) - this->_container;
			size_type after_pos = this->_end - &(*position);
			while (first != last)
			{
				temp1.push_back(*first);
				first++;
				i++;
			}
			while (after_pos > 0)
			{
				temp2.push_back(*(position + k));
				k++;
				after_pos--;
			}
			if (this->size() + temp1.size() > this->_capacity)
				this->reserve(this->size() + temp1.size());
			while (i > 0)
			{
				this->push_back(*(this->begin()));
				i--;
			}
			for (iterator it = temp1.begin(); it != temp1.end(); it++)
			{
				*(this->_container + pos) = *it;
				pos++;
			}
			for (iterator it = temp2.begin(); it != temp2.end(); it++)
			{
				*(this->_container + pos) = *it;
				pos++;
			}
		}

		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename enable_if<!is_integral<InputIterator>::value>::type* = NULL,
					typename enable_if<!is_same<typename iterator_traits<InputIterator>::iterator_category, std::input_iterator_tag>::value>::type* = NULL)
		{
			size_type n = ft::distance(first, last);
			if (this->_capacity >= n + this->size())
			{
				for (size_type i = 0; i < (this->size() - (&(*position) - this->_container)); i++)
					this->_alloc.construct(this->_end - i + n - 1, *(this->_end - i - 1));
				this->_end += n;
				while (first != last)
				{
					this->_alloc.construct(&(*position), *first);
					first++;
					position++;
				}
			}
			else
			{
				size_type allocation_size;
				if (this->_capacity == 0)
					 allocation_size = n;
				else
					// allocation_size = this->_capacity;
					allocation_size = (this->size() + n);
				// while (allocation_size < (this->size() + n))
				// 	allocation_size = allocation_size * 2;
				pointer new_start = this->_alloc.allocate(allocation_size);
				pointer new_end = new_start + this->size() + n;
				for (int i = 0; i < &(*position) - this->_container; i++)
					this->_alloc.construct(new_start + i, *(this->_container + i));
					
				for (int j = 0; first != last; first++, j++)
					this->_alloc.construct(new_start + (&(*position) - this->_container) + j, *first);
					
				for (size_type k = 0; k < this->size() - (&(*position) - this->_container); k++)
					this->_alloc.construct(new_start + (&(*position) - this->_container) + n + k, *(&(*position) + k));
					
				for (size_type l = 0; l < this->size(); l++)
					this->_alloc.destroy(this->_container + l);
				if (this->_container)
					this->_alloc.deallocate(this->_container, this->capacity());
				this->_container = new_start;
				this->_end = new_end;
				this->_capacity = allocation_size;
			}
		}

		iterator erase(iterator position)											
		{
			iterator it = begin();
			size_type i = 0;
			while (it != position)
			{
				i++;
				it++;
			}
			while ((i + 1) < size())
			{
				this->_container[i] = this->_container[i + 1];
				i++;
			}
			this->_alloc.destroy(&(this->_container[i]));
			this->_end--;
			return (it);
		}

		iterator erase(iterator first, iterator last)
		{	
			iterator it = begin();
			size_type i = 0;
			size_type diff = last - first;
			while (it != first)
			{
				i++;
				it++;
			}
			size_type y = i;
			while (first != last)
			{
				i++;
				first++;
			}
			while (i < size())
			{
				this->_container[y] = this->_container[i];
				i++;
				y++;
			}
			this->_end -= i - y;
			for (size_type x = 0; x < diff; x++)
				this->_alloc.destroy(&(this->_container[y++]));
			return (it);
		}

		void swap(vector &x)
		{
			pointer x_start = x._container;
			pointer x_end = x._end;
			size_type x_capacity = x._capacity;
			allocator_type x_alloc = x._alloc;

			x._container = this->_container;
			x._end = this->_end;
			x._capacity = this->_capacity;
			x._alloc = this->_alloc;

			this->_container = x_start;
			this->_end = x_end;
			this->_capacity = x_capacity;
			this->_alloc = x_alloc;
		}

		void clear(void)
		{
			size_type size = this->size();
			for (size_type i = 0; i < size; i++)
			{
				this->_alloc.destroy(&(this->_container[i]));
			}
			this->_end = this->_container;
		}

		allocator_type get_allocator(void) const
		{
			return (this->_alloc);
		}

	};

	template <typename T, typename Allocator>
	bool operator==(const vector<T, Allocator> &lhs, const vector<T,Allocator> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename vector<T, Allocator>::const_iterator lhsIteratorBegin = lhs.begin();
		typename vector<T, Allocator>::const_iterator rhsIteratorBegin = rhs.begin();
		while (lhsIteratorBegin != lhs.end())
		{
			if (*lhsIteratorBegin != *rhsIteratorBegin || rhsIteratorBegin == rhs.end())
				return (false);
			lhsIteratorBegin++;
			rhsIteratorBegin++;
		}
		return (true);
	}
	
	template <typename T, typename Allocator>
	bool operator!=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		if (!(lhs == rhs))
			return true;
		return false;
	}
	
	template <typename T, typename Allocator> bool
	operator<(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	
	template <typename T, typename Allocator>
	bool operator<=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		if (!(rhs < lhs))
			return (true);
		return (false);
	}
	
	template <typename T, typename Allocator>
	bool operator>(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		if (rhs < lhs)
			return (true);
		return (false);
	}
	
	template <typename T, typename Allocator>
	bool operator>=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		if (!(lhs < rhs))
			return (true);
		return (false);
	}
	

	template <class T, class Allocator>
	void swap(vector<T,Allocator> &x, vector<T,Allocator> &y)
	{
		x.swap(y);
	}
}

#endif
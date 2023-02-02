/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguth <tguth@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:32:44 by ben               #+#    #+#             */
/*   Updated: 2023/02/01 06:11:08 by tguth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

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
		typedef typename ft::Iterator<T, false>						iterator;
		typedef typename ft::Iterator<T, true>						const_iterator;
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
		explicit vector(const allocator_type &alloc = allocator_type())																								//*Checked
			: _alloc(alloc), _container(NULL), _end(NULL), _capacity(0) {}

		/* Fill constructor */
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())											//*Checked
			: _alloc(alloc), _container(NULL), _end(NULL), _capacity(0)
		{
			_container = _alloc.allocate(n);
			_capacity = n;
			_end = _container;
			while (n--)
			{
				_alloc.construct(_end, val);
				_end++;
			}
		}

		/* Range constructor */
		/* enable_if is needed because range constructor is a better match then fill constructor (for example two numbers)*/
		template<class InputIterator>
		vector(InputIterator first, InputIterator last,																											//*Checked
				const allocator_type &alloc = allocator_type(),
				typename enable_if<!is_integral<InputIterator>::value>::type* = NULL) : _alloc(alloc)
		{
			this->_alloc = alloc;
			this->_capacity = ft::distance(first, last);
			this->_container = _alloc.allocate(this->_capacity);
			this->_end = this->_container;
			while (first != last)
			{
				_alloc.construct(this->_end, *first);
				first++;
				this->_end++;
			}
		}

		/* Copy Constructor */
		vector(const vector &rhs) : _alloc(rhs._alloc), _container(NULL), _end(NULL), _capacity(0)																	//*Checked
		{
			this->insert(this->begin(), rhs.begin(), rhs.end());
		}

		/* Deconstructor */
		~vector()
		{
			this->clear();
			this->_alloc.deallocate(this->_container, this->capacity());
		}

		/* Assignment operator */
		vector &operator=(const vector &rhs)																														//*Checked
		{
			if (rhs == *this)
				return (*this);
			this->clear();
			this->insert(this->end(), rhs.begin(), rhs.end());
			return (*this);
		}

		/* returns iterator of first element */
		iterator begin(void)																											//*Checked
		{
			return (iterator(this->_container));
		}

		/* const version of the above */
		const_iterator begin(void) const
		{
			return (const_iterator(this->_container));
		}

		iterator end(void)																		//*Checked
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

		reverse_iterator rbegin(void)											//*Checked
		{
			return (reverse_iterator(this->_end));
		}

		const_reverse_iterator rbegin(void) const
		{
			return (reverse_iterator(this->_end));
		}

		reverse_iterator rend(void)											//*Checked
		{
			return (reverse_iterator(this->_container));
		}

		const_reverse_iterator rend(void) const
		{
			return (reverse_iterator(this->_container));
		}

		size_type size(void) const											//*Checked
		{
			return (this->_end - this->_container);
		}

		size_type max_size(void) const											//*Checked
		{
			return (allocator_type().max_size());
		}

		void resize(size_type n, value_type val = value_type())											//*Checked
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

		/* returns the capacity of the container */
		size_type capacity(void) const											//*Checked
		{
			return (this->_capacity);
		}

		bool empty(void) const											//*Checked
		{
			if (this->size() == 0)
				return (true);
			return (false);
		}

		void reserve(size_type n)											//*Checked
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
				this->_alloc.deallocate(prev_start - prev_size, prev_capacity);
			}
		}

		reference operator[](size_type n)											//*Checked
		{
			return (*(this->_container + n));
		}

		const_reference operator[](size_type n) const
		{
			return (*(this->_container + n));
		}

		/* Returns a reference to the element at position n in the vector 	*/
		/* https://cplusplus.com/reference/vector/vector/at/				*/
		reference at(size_type n)													//*Checked
		{
			if (n >= this->size())
				throw std::out_of_range("Out of Range");
			return ((*this)[n]);
		}

		/* const version of above */
		const_reference at(size_type n) const
		{
			if (n >= this->size())
				throw std::out_of_range("Out of Range");
			return ((*this)[n]);
		}

		reference front(void)											//*Checked
		{
			return (*this->_container);
		}

		const_reference front(void) const
		{
			return (*this->_container);
		}

		/* reference to last element in array */
		reference back(void)											//*Checked
		{
			return (*(this->_end - 1));
		}

		/* const version of the above */
		const_reference back(void) const
		{
			return (*(this->_end - 1));
		}

		/* Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly. 	*/
		/* https://cplusplus.com/reference/vector/vector/assign/ 													*/
		template<class InputIterator>
		void assign(InputIterator first, InputIterator last,											//*Checked
					typename enable_if<!is_integral<InputIterator>::value>::type* = NULL)
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
				this->_alloc.deallocate(this->_container, this->capacity());
				this->_container = new_start;
				this->_end = new_end;
				this->_capacity = new_capacity;
			}
		}

		/* Fill Assign */
		void assign(size_type n, const value_type &val)											//*Checked
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

		void push_back(const value_type &val)											//*Checked
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

		void pop_back(void)																	//*Checked
		{
			this->_alloc.destroy(&(this->back()));
			this->_end--;
		}

		iterator insert(iterator position, const value_type &val)											//*Checked
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

		void insert(iterator position, size_type n, const value_type &val)											//*Checked
		{
			if (n == 0)
				return ;
			if (n > this->max_size())
				throw std::length_error("vector::insert");
			size_type pos = &(*position) - this->_container;
			if (this->_capacity >= n + size())
			{
				for (size_type i = 0; i < this->size() - pos; i++)
					this->_alloc.construct(this->_end - i + (n - 1), *(this->_end - i - 1));
				this->_end += n;
				while (n)
				{
					this->_alloc.construct(&(*position) + (n - 1), val);
					n--;
				}
			}
			else
			{
				size_type new_capacity;
				if (this->size() == 0)
					new_capacity = 0;
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
				this->_alloc.deallocate(this->_container, this->capacity());
				this->_container = new_start;
				this->_end = new_end;
				this->_capacity = new_capacity;
			}
		}

		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,											//*Checked
					typename enable_if<!is_integral<InputIterator>::value>::type* = NULL)
		{
			size_type n = ft::distance(first, last);
			if (this->_capacity >= n + size())
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
				pointer new_start = this->_alloc.allocate(this->size() + n);
				pointer new_end = new_start + this->size() + n;
				size_type new_capacity = this->size() + n;
				for (int i = 0; i < &(*position) - this->_container; i++)
					this->_alloc.construct(new_start + i, *(this->_container + i));
					
				for (int j = 0; first != last; first++, j++)
					this->_alloc.construct(new_start + (&(*position) - this->_container) + j, *first);
					
				for (size_type k = 0; k < this->size() - (&(*position) - this->_container); k++)
					this->_alloc.construct(new_start + (&(*position) - this->_container) + n + k, *(&(*position) + k));
					
				for (size_type l = 0; l < this->size(); l++)
					this->_alloc.destroy(this->_container + l);
				this->_alloc.deallocate(this->_container, this->capacity());
				this->_container = new_start;
				this->_end = new_end;
				this->_capacity = new_capacity;
			}
		}

		iterator erase(iterator position)											
		{
			pointer pos = &(*position);
			this->_alloc.destroy(pos);

			if(position + 1 == end())
			{
				this->_end--;
				return pos;
			}
			iterator it = position;
			for (; it + 1 != end(); it++)
				this->_alloc.construct(&(*it), (*(it + 1)));
			this->_alloc.destroy(&(*it));
			this->_end--;
			return (iterator(pos));
		}

		iterator erase(iterator first, iterator last)
		{
			pointer firstPos = &(*first);
			while (first != last)
			{
				this->_alloc.destroy(&(*first));
				first++;
			}
			for (int i = 0; i < this->_end - &(*last); i++)
			{
				this->_alloc.construct(firstPos + i, *(&(*last) + i));
				this->_alloc.destroy(&(*last) + i);
			}
			this->_end -= &(*last) - firstPos;
			return (iterator(firstPos));
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
				this->_end--;
				this->_alloc.destroy(this->_end);
			}
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
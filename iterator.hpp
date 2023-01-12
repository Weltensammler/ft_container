/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:33:09 by ben               #+#    #+#             */
/*   Updated: 2022/11/24 16:33:11 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "helpers.hpp"

namespace ft
{
	template <typename T>
	class vector_Iterator: public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
		
		private:

			pointer _element;
		
		public:

			vector_Iterator(void) : _element(NULL) {}
			
			vector_Iterator(const vector_Iterator &copy) : _element(copy._element) {}
			
			vector_Iterator(pointer element) : _element(element) {}
			
			vector_Iterator &operator=(const vector_Iterator &iter)
			{
				if (*this == iter)
					return (*this);
				this->_element = iter._element;
				return (*this);
			}
			
			virtual ~vector_Iterator(void) {}

			pointer base(void) const
			{
				return (this->_element);
			}

			reference operator*(void) const
			{
				return (*(this->_element));
			}

			pointer operator->(void)
			{
				return (&(this->operator*()));
			}
			
			vector_Iterator operator++(int)
			{
				vector_Iterator tmp = *this;
				this->_element++;
				return (tmp);
			}
			
			vector_Iterator &operator++(void)
			{
				this->_element++;
				return (*this);
			}
			
			vector_Iterator operator--(int)
			{
				vector_Iterator tmp = *this;
				this->_element--;
				return (tmp);
			}
			
			vector_Iterator &operator--(void)
			{
				this->_element--;
				return (*this);
			}

			vector_Iterator operator+(difference_type n) const
			{
				return (this->_element + n);	
			}

			vector_Iterator &operator+=(difference_type n)
			{
				this->_element += n;
				return (*this);
			}
			
			vector_Iterator operator-(difference_type n) const
			{
				return (this->_element - n);
			}

			vector_Iterator &operator-=(difference_type n)
			{
				this->_element -= n;
				return (*this);
			}

			bool operator==(const vector_Iterator<T> &rhs)
			{
				return (this->base() == rhs.base());
			}

			bool operator!=(const vector_Iterator<T> &rhs)
			{
				return (this->base() != rhs.base());
			}

			bool operator>(const vector_Iterator<T> &rhs)
			{
				return (this->base() > rhs.base());
			}

			bool operator>=(const vector_Iterator<T> &rhs)
			{
				return (this->base() >= rhs.base());
			}

			bool operator<(const vector_Iterator<T> &rhs)
			{
				return (this->base() > rhs.base());
			}

			bool operator<=(const vector_Iterator<T> &rhs)
			{
				return (this->base() >= rhs.base());
			}

			reference operator[](difference_type n)
			{
				return (*(this->_element + n));
			}

	};

	template<typename T>
	vector_Iterator<T> operator+(typename vector_Iterator<T>::difference_type n, vector_Iterator<T> &it)
	{
		return (&(*it) + n);
	}

	template<typename T>
	typename vector_Iterator<T>::difference_type operator-(const vector_Iterator<T> &lhs, const vector_Iterator<T> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template<typename T>
	typename vector_Iterator<T>::difference_type operator-(const vector_Iterator<const T> &lhs, const vector_Iterator<T> &rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif
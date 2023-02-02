/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:33:09 by ben               #+#    #+#             */
/*   Updated: 2023/01/31 12:58:26 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "helpers.hpp"

namespace ft
{
	template <typename T, bool isConst>
	class vector_Iterator: public ft::iterator<ft::random_access_iterator_tag, T, isConst>
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T, isConst>::value_type value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T, isConst>::difference_type difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T, isConst>::pointer pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T, isConst>::reference reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T, isConst>::iterator_category iterator_category;
		
		private:

			pointer _element;
		
		public:

			vector_Iterator(void) : _element(NULL) {}
			
			vector_Iterator(const vector_Iterator &copy) : _element(copy._element) {}
			
			vector_Iterator(pointer element) : _element(element) {}
			
			template<typename TypeT, bool TypeisConst>
			vector_Iterator &operator=(const vector_Iterator<TypeT, TypeisConst > &iter)
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
			
			//template<typename Type, bool iConst>
			vector_Iterator operator++(int)
			{
				vector_Iterator<T, isConst> tmp = *this;
				this->_element++;
				return (tmp);
			}
			
			vector_Iterator &operator++(void)
			{
				this->_element++;
				return (*this);
			}
			
			// template<typename Type, bool iConst>
			vector_Iterator operator--(int)
			{
				vector_Iterator<T, isConst> tmp = *this;
				this->_element--;
				return (tmp);
			}
			
			// template<typename Type, bool iConst>
			vector_Iterator &operator--(void)
			{
				this->_element--;
				return (*this);
			}

			//template<typename Type, bool iConst>
			vector_Iterator operator+(difference_type n) const
			{
				return (this->_element + n);	
			}

			//template<typename Type, bool iConst>
			vector_Iterator &operator+=(difference_type n)
			{
				this->_element += n;
				return (*this);
			}
			
			//template<typename Type, bool iConst>
			vector_Iterator operator-(difference_type n) const
			{
				return (this->_element - n);
			}

			//template<typename Type, bool iConst>
			vector_Iterator &operator-=(difference_type n)
			{
				this->_element -= n;
				return (*this);
			}

			template<typename Type, bool iConst>
			bool operator==(const vector_Iterator<Type, iConst> &rhs) const
			{
				return (this->base() == rhs.base());
			}

			template<typename Type, bool iConst>
			bool operator!=(const vector_Iterator<Type, iConst> &rhs) const
			{
				return (this->base() != rhs.base());
			}

			template<typename Type, bool iConst>
			bool operator>(const vector_Iterator<Type, iConst> &rhs) const
			{
				return (this->base() > rhs.base());
			}

			template<typename Type, bool iConst>
			bool operator>=(const vector_Iterator<Type, iConst> &rhs) const
			{
				return (this->base() >= rhs.base());
			}

			template<typename Type, bool iConst>
			bool operator<(const vector_Iterator<Type, iConst> &rhs) const
			{
				return (this->base() > rhs.base());
			}

			template<typename Type, bool iConst>
			bool operator<=(const vector_Iterator<Type, iConst> &rhs) const
			{
				return (this->base() >= rhs.base());
			}

			reference operator[](difference_type n)
			{
				return (*(this->_element + n));
			}

	};

	template<typename Type, bool iConst>
	vector_Iterator<Type, iConst> operator+(typename vector_Iterator<Type, iConst>::difference_type n, vector_Iterator<Type, iConst> &it)
	{
		return (&(*it) + n);
	}

	template<typename Type, bool iConst>
	typename vector_Iterator<Type, iConst>::difference_type operator-(const vector_Iterator<Type, iConst> &lhs, const vector_Iterator<Type, iConst> &rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif
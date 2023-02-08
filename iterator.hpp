/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschende <bschende@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:33:09 by ben               #+#    #+#             */
/*   Updated: 2023/02/03 14:03:519 by bschende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <stddef.h>
#include <sstream>

namespace ft
{
	struct input_iterator_tag											{};
	struct output_iterator_tag											{};
	struct forward_iterator_tag			: input_iterator_tag			{};
	struct bidirectional_iterator_tag	: forward_iterator_tag			{};
	struct random_access_iterator_tag	: bidirectional_iterator_tag	{};
	
	template<class Iterator>
	struct iterator_traits
	{

		typedef typename Iterator::difference_type						difference_type;
		typedef typename Iterator::value_type							value_type;
		typedef typename Iterator::pointer								pointer;
		typedef typename Iterator::reference							reference;
		typedef typename Iterator::iterator_category					iterator_category;
	};

	template<typename T>
	struct iterator_traits<T*>
	{

		typedef ptrdiff_t												difference_type;
		typedef T														value_type;
		typedef T*														pointer;
		typedef T&														reference;
		typedef random_access_iterator_tag								iterator_category;
	};

	template<typename T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t												difference_type;
		typedef T														value_type;
		typedef const T*												pointer;
		typedef const T&												reference;
		typedef random_access_iterator_tag								iterator_category;
	};

	template< typename T>
	class Iterator
	{
		public:
			typedef typename iterator_traits<T*>::iterator_category		iterator_category;
			typedef typename iterator_traits<T*>::value_type 			value_type;
			typedef typename iterator_traits<T*>::reference 			reference;
			typedef typename iterator_traits<T*>::pointer				pointer;
			typedef typename iterator_traits<T*>::difference_type		difference_type;
			typedef T													iterator_type;

		private:
			pointer 	_ptr;

		public:

			Iterator() : _ptr() {}

			Iterator(pointer a) : _ptr(a) {}

			~Iterator() {}

			template <class U>
			Iterator(const Iterator<U>& src) : _ptr(src.base()) {
			}

			pointer base() const { return (_ptr);}

			Iterator& operator=(const Iterator<T>& rhs) 
			{
				if (this == &rhs)
					return *this;
				_ptr = rhs.base();
				return (*this);
			}

			Iterator & operator++() 
			{
				++_ptr;
				return (*this);
			}

			Iterator operator++(int) 
			{
				Iterator tmp(*this);
				++_ptr;
				return (tmp);
			}

			Iterator & operator--() 
			{
				--_ptr;
				return (*this);
			}

			Iterator  operator--(int) 
			{
				Iterator tmp = *this;
				--_ptr;
				return tmp;
			}
			Iterator operator+(const difference_type & n) const {return (_ptr + n);}

			Iterator operator-(const difference_type & n) const {return (_ptr - n);}

			Iterator & operator+=(const difference_type & a)
			{
				_ptr += a;
				return (*this);
			}

			Iterator & operator-=(const difference_type & a)
			{
				_ptr -= a;
				return (*this);
			}

			pointer operator->() const {return (_ptr);}

			reference operator*() const {return (*_ptr);}

			reference operator[](difference_type n) const {return (_ptr[n]);}
		};

		template<typename A, typename B>
		bool operator==(const Iterator<A> & lhs, const Iterator<B> & rhs)
		{
			return &(*lhs) == &(*rhs);
		}

		template<typename A, typename B>
		bool operator!=(const Iterator<A> & lhs, const Iterator<B> & rhs) 
		{
			return &(*lhs) != &(*rhs);
		}

		template<typename A, typename B>
		bool operator>(const Iterator<A> & lhs, const Iterator<B> & rhs) 
		{
			return &(*lhs) > &(*rhs);
		}

		template<typename A, typename B>
		bool operator<(const Iterator<A> & lhs, const Iterator<B> & rhs) 
		{
			return &(*lhs) < &(*rhs);
		}

		template<typename A, typename B>
		bool operator<=(const Iterator<A> & lhs, const Iterator<B> & rhs) 
		{
			return &(*lhs) <= &(*rhs);
		}

		template<typename A, typename B>
		bool operator>=(const Iterator<A> & lhs, const Iterator<B> & rhs) 
		{
			return &(*lhs) >= &(*rhs);
		}

		template<typename A, typename B>
		typename Iterator<A>::difference_type operator-(const Iterator<A> & lhs,
														const Iterator<B> & rhs)
		{
			return &(*lhs) - &(*rhs);
		}

		template<typename A, typename B>
		typename Iterator<A>::difference_type operator+(const Iterator<A> & lhs,
														const Iterator<B> & rhs)
		{
			return &(*lhs) + &(*rhs);
		}

		template<typename L>
		typename ft::Iterator<L> operator+(	const typename Iterator<L>::difference_type & a,
											const Iterator<L> & iter)
		{
			return	(iter + a);
		}

		template<typename L>
		typename ft::Iterator<L> operator-(	const typename ft::Iterator<L>::difference_type & a,
											const ft::Iterator<L> & iter)
		{
			return	(iter - a);
		}

	template <class Iterator>
	class reverse_Iterator
	{

		public:

			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		
		private:

			iterator_type	_iter;

		public:
			
			reverse_Iterator(void) : _iter() {}
			
			explicit reverse_Iterator(iterator_type iterType) : _iter(iterType) {}

			template <class Iter>
			reverse_Iterator(const reverse_Iterator<Iter> &reverseIter) : _iter(reverseIter.base()) {}

			reverse_Iterator &operator=(const reverse_Iterator &rhs)
			{
				if (*this == rhs)
					return (*this);
				this->_iter = rhs._iter;
				return (*this);
			}

			virtual ~reverse_Iterator(void) {}

			iterator_type base(void) const {return (this->_iter);}

			reference operator*(void) const
			{
				Iterator temp = this->_iter;
				temp--;
				return (*temp);
			}

			reverse_Iterator operator+(difference_type n) const
			{
				return (reverse_Iterator(this->_iter - n));
			}
			
			reverse_Iterator &operator++(void)
			{
				this->_iter--;
				return (*this);
			}
			
			reverse_Iterator operator++(int)
			{
				reverse_Iterator temp = *this;
				++(*this);
				return (temp);
			}
			
			reverse_Iterator &operator+=(difference_type n)
			{
				*this = *this + n;
				return (*this);
			}
			
			reverse_Iterator operator-(difference_type n) const
			{
				return (reverse_Iterator(this->_iter + n));
			}
			
			reverse_Iterator &operator--(void)
			{
				this->_iter++;
				return (*this);
			}
			
			reverse_Iterator operator--(int)
			{
				reverse_Iterator temp = *this;
				--(*this);
				return (temp);
			}
			
			reverse_Iterator &operator-=(difference_type n)
			{
				*this = *this - n;
				return (*this);
			}
			
			pointer operator->(void) const {return (&(operator*()));}
			
			reference operator[](difference_type n) const {return (this->base()[-n - 1]);}
	};

	template<class Iter1, class Iter2 >
	bool operator==(	const reverse_Iterator<Iter1>& lhs,
						const reverse_Iterator<Iter2>& rhs )
	{
		return lhs.base() == rhs.base();
	}

	template< class Iter1, class Iter2 >
	bool operator!=(	const reverse_Iterator<Iter1>& lhs,
						const reverse_Iterator<Iter2>& rhs )
	{
		return lhs.base() != rhs.base();
	}

	template< class Iter1, class Iter2 >
	bool operator<(		const reverse_Iterator<Iter1>& lhs,
						const reverse_Iterator<Iter2>& rhs )
	{
		return lhs.base() > rhs.base();
	}

	template< class Iter1, class Iter2 >
	bool operator<=(	const reverse_Iterator<Iter1>& lhs,
						const reverse_Iterator<Iter2>& rhs )
	{
		return lhs.base() >= rhs.base();
	}

	template< class Iter1, class Iter2 >
	bool operator>(		const reverse_Iterator<Iter1>& lhs,
						const reverse_Iterator<Iter2>& rhs )
	{
		return lhs.base() < rhs.base();
	}

	template< class Iter1, class Iter2 >
	bool operator>=(	const reverse_Iterator<Iter1>& lhs,
						const reverse_Iterator<Iter2>& rhs )
	{
		return lhs.base() <= rhs.base();
	}

	template< class Iter >
	reverse_Iterator<Iter>	operator+(	typename reverse_Iterator<Iter>::difference_type n,
										const reverse_Iterator<Iter>& it )
	{
		return reverse_Iterator<Iter>(it.base() - n);
	}

	template< class Iter1, class Iter2 >
	typename reverse_Iterator<Iter1>::difference_type	operator-(	const reverse_Iterator<Iter1>& lhs,
																	const reverse_Iterator<Iter2>& rhs )
	{
		return rhs.base() - lhs.base();
	}

	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last)
		{
			first++;
			n++;
		}
		return (n);
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(	InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(	InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return (false);
			else if (comp(*first1, *first2))
				return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	/* enable_if */
	template <bool, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	/* is_integral */
	template <class T, T v>
	struct integral_constant
	{
		static const T						value = v;
		typedef T							valueType;
		typedef integral_constant<T, v>		type;
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	//non-itegral types
	template <class T> struct is_integral : false_type {};

	//integral types
	template <> struct is_integral<bool>					: true_type {};
	template <> struct is_integral<char>					: true_type {};
	template <> struct is_integral<wchar_t>					: true_type {};
	template <> struct is_integral<signed char>				: true_type {};
	template <> struct is_integral<short int>				: true_type {};
	template <> struct is_integral<int>						: true_type {};
	template <> struct is_integral<long int>				: true_type {};
	template <> struct is_integral<long long int>			: true_type {};
	template <> struct is_integral<unsigned char>			: true_type {};
	template <> struct is_integral<unsigned short int>		: true_type {};
	template <> struct is_integral<unsigned int>			: true_type {};
	template <> struct is_integral<unsigned long int>		: true_type {};
	template <> struct is_integral<unsigned long long int>	: true_type {};

	template <class T1, class T2>
	class pair
	{
		public:
			
			typedef T1 firstValueType;
			typedef T2 secondValueType;

			firstValueType first;
			secondValueType second;

			pair(void) : first(), second() {}

			pair(const firstValueType &a, const secondValueType &b) : first(a), second(b) {}

			template <class U, class V>
			pair(const pair<U, V> &copy) : first(copy.first), second(copy.second) {}
			
			pair &operator=(const pair &rhs)
			{
				if (this == &rhs)
					return (*this);
				this->first = rhs.first;
				this->second = rhs.second;
				return (*this);
			}
			~pair(void) {}
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first < rhs.first || lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

		template <bool flag, class IsTrueType, class IsFalseType>
	struct choose;

	template <class IsTrueType, class IsFalseType>
	struct choose<true, IsTrueType, IsFalseType>
	{
		typedef IsTrueType type;
	};

	template <class IsTrueType, class IsFalseType>
	struct choose<false, IsTrueType, IsFalseType>
	{
		typedef IsFalseType type;
	};

		template <class InputIterator1, class InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
				return (false);
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(pred(*first1 == *first2)))
				return (false);
		}
		return (true);
	}
}

#endif
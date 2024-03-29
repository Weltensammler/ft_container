/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:56:28 by ben               #+#    #+#             */
/*   Updated: 2023/03/02 13:56:30 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{

	template<	typename T,
				typename Container = ft::vector<T> >
	class stack
	{
		public:

			typedef	T											value_type;
			typedef Container									container_type;
			typedef	std::size_t									size_type;
			typedef typename container_type::pointer			pointer;
            typedef typename container_type::const_pointer		const_pointer;
            typedef typename container_type::reference			reference;
            typedef typename container_type::const_reference	const_reference;
		
		protected:

			container_type	c;

		public:

			/* Constructor */
			explicit stack(const container_type &cont = container_type()): c(cont) {}

			stack(const stack &other): c(other.c) {}
			
			/* Deconstructor */
			~stack() {}

			stack& operator=(const stack &rhs)
			{
				if (*this == rhs)
					return (*this);
				this->c = rhs.c;
				return (*this);
			}

			value_type& top() {return (c.back());}

			const value_type& top() const {return (c.back());}

			bool empty() const {return (c.empty());}

			size_type size() const {return( c.size());}

			void push(const value_type &value) {c.push_back(value);}

			void pop() {c.pop_back();}
			
			friend
			bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (lhs.c == rhs.c);
			}

			friend
			bool operator!=  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (lhs.c != rhs.c);
			}

			friend
			bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (lhs.c < rhs.c);
			}

			friend
			bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (lhs.c > rhs.c);
			}

			friend
			bool operator>=  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (lhs.c >= rhs.c);
			}

			friend
			bool operator<=  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (lhs.c <= rhs.c);
			}
	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs == rhs);
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs != rhs);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs <= rhs);
	}

	template <class T, class Container>
	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs < rhs);
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs > rhs);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs >= rhs);
	}
}

#endif
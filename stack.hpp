/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschende <bschende@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:32:33 by ben               #+#    #+#             */
/*   Updated: 2023/02/08 16:47:59 by bschende         ###   ########.fr       */
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

			typedef	T				value_type;
			typedef Container		container_type;
			typedef	std::size_t		size_type;
		
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
			bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (lhs.c < rhs.c);
			}
	};

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
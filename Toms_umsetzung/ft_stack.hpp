/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:32:33 by ben               #+#    #+#             */
/*   Updated: 2023/01/12 12:57:16 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "ft_vector.hpp"

namespace ft
{

	template<	typename T,
				typename Container = vector<T> >
	class stack
	{
		public:
			typedef Container								container_type;
			typedef typename Container::value_type			value_type;
			typedef typename Container::size_type			size_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;
		
		protected:

			container_type	c;
			
		public:

			/* Constructor */
			explicit stack(const Container &cont = Container()): c(cont) {}

			/* Deconstructor */
			~stack() {}

			stack &operator=(const stack &other)
			{
				if (*this == other)
					return (*this);
				this->c = other.c;
				return (*this);
			}

			reference top()
			{
				return (c.back());
			}

			const_reference top() const
			{
				return (c.back());
			}

			bool empty() const
			{
				return (c.empty());
			}

			size_type size() const
			{
				return( c.size());
			}

			void push(const value_type &value)
			{
				c.push_back(value);
			}

			void pop()
			{
				c.pop_back();
			}
	};

			template <class T, class Container>  bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (lhs.c == rhs.c);
			}

			template <class T, class Container>  bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (!(lhs.c == rhs.c));
			}

			template <class T, class Container>  bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (lhs.c < rhs.c);
			}

			template <class T, class Container>  bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (!(lhs.c >= rhs.c));
			}

			template <class T, class Container>  bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (!(lhs.c < rhs.c));
			}

			template <class T, class Container>  bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
			{
				return (rhs.c >= lhs.c);
			}
}

#endif
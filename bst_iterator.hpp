/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartkow <jbartkow@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:32:13 by ben               #+#    #+#             */
/*   Updated: 2023/02/09 16:24:13 by jbartkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_ITERATOR_HPP
# define BST_ITERATOR_HPP


#include "iterator.hpp"
#include "bst.hpp"
#include "map.hpp" //hier nicht

namespace ft
{

	template <typename key, bool isConst>
	class BST_iter
	{
		public:
		typedef key 																					key_type;
		typedef const key_type																			const_key_type;
		typedef	key_type																				normal_key_type;
		typedef typename choose<isConst, const_key_type, normal_key_type>::type							value_type;
		typedef typename ft::Iterator<value_type>::difference_type										difference_type;
		typedef typename ft::Iterator<value_type>::pointer												pointer;
		typedef typename ft::Iterator<value_type>::reference											reference;
		typedef typename ft::Iterator<value_type>::iterator_category									iterator_category;
		
		private:
		typedef const node<key>												const_node;
		typedef node<key>													normal_node;
		typedef typename choose<isConst, const_node, normal_node>::type *	node_ptr;
		
		node_ptr _p;
		node_ptr _first;
		node_ptr _last;

		public:

			BST_iter(): _p(NULL), _first(NULL), _last(NULL) {
			}

			BST_iter(node_ptr nd, node_ptr f = NULL, node_ptr l = NULL): _p(nd), _first(f), _last(l) {
			}

			~BST_iter() {}

			BST_iter(const BST_iter &it) : _p(it._p), _first(it._first), _last(it._last) {
			}

			
			template<typename TypeKey, bool TypeIsConst>
			BST_iter(BST_iter<TypeKey, TypeIsConst> const & other) : _p(other.getPtr()), _first(other.getf()), _last(other.getl()){
			}
			node_ptr getPtr() const
			{
				return (this->_p);
			}
			
			node_ptr getf() const
			{
				return (this->_first);
			}
			
			node_ptr getl() const
			{
				return (this->_last);
			}

			BST_iter const &operator=(const BST_iter &other)
			{
				_p = other.getPtr();
				_first = other.getf();
				_last = other.getl();
				return (*this);
			}

			BST_iter &operator++()
			{
				if (!_p)
					_p = _first;
				else if (_p->right != NULL)
				{
					_p = _p->right;
					while (_p->left != NULL)
						_p = _p->left;
				}
				else
				{
					node_ptr tmp = _p->parent;
					while (tmp != NULL && _p == tmp->right)
					{
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}

			BST_iter operator++(int)
			{
				BST_iter tmp = *this;
				++(*this);
				return tmp;
			}

			BST_iter &operator--()
			{
				if (!_p)
					_p = _last;
				else if (_p->left != NULL)
				{
					_p = _p->left;
					while (_p->right != NULL)
						_p = _p->right;
				}
				else
				{
					node_ptr tmp = _p->parent;
					while (tmp != NULL && _p == tmp->left)
					{
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}

			BST_iter operator--(int)
			{
				BST_iter tmp = *this;
				--(*this);
				return (tmp);
			}

			const BST_iter operator--(int) const
			{
				BST_iter tmp = *this;
				--(*this);
				return (tmp);
			}

			value_type *operator->() const
			{
				return (&(_p->data));
			}

			value_type &operator*() const
			{
				return (static_cast<node_ptr>(_p)->data);
			}

			bool operator==(const BST_iter & src)
			{
				return (this->_p == src._p);
			}

			bool operator!=(const BST_iter & src)
			{
				return (this->_p != src._p);
			}
	};
	
	template <typename Iterator>
	class reverse_BST_iter
	{
		public:
		typedef Iterator													iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;

		private:
		iterator_type	_base;

		public:
		reverse_BST_iter(void)
		{
		}

		explicit reverse_BST_iter (iterator_type it) : _base(it)
		{
		}

		reverse_BST_iter (const reverse_BST_iter<Iterator>& rev_it) : _base(rev_it._base)
		{
		}
		
		template< class Iter >
		reverse_BST_iter(const reverse_BST_iter<Iter>& rev_it) : _base(rev_it.base())
		{
		}
		
		reverse_BST_iter const & operator=(reverse_BST_iter const & rhs)
		{
			this->_base = rhs._base;
			return (*this);
		}

		iterator_type base() const
		{
			return (this->_base);
		}
		
		reference	operator*() const
		{
			iterator_type	tmp(this->_base);
			--tmp;
			return (*tmp);
		}
		
		pointer operator->() const
		{
			return (&(operator*()));
		}

		reverse_BST_iter &	operator++()
		{
			--(this->_base);
			return (*this);
		}
		
		reverse_BST_iter	operator++(int)
		{
			reverse_BST_iter tmp(this->_base);
			--(this->_base);
			return (tmp);
		}
		
		reverse_BST_iter& operator--()
		{
			++(this->_base);
			return (*this);
		}
		
		reverse_BST_iter  operator--(int)
		{
			reverse_BST_iter tmp(this->_base);
			++(this->_base);
			return (tmp);
		}
		

	};

	template <class Iterator>
	bool operator== (const reverse_BST_iter<Iterator>& lhs, const reverse_BST_iter<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!= (const reverse_BST_iter<Iterator>& lhs, const reverse_BST_iter<Iterator>& rhs)
	{
		return !(lhs.base() == rhs.base());
	}
}

#endif

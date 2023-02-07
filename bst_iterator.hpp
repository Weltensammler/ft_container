/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:32:13 by ben               #+#    #+#             */
/*   Updated: 2023/02/07 13:06:42 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_ITERATOR_HPP
# define BST_ITERATOR_HPP


#include "iterator.hpp"
#include "bst.hpp"

namespace ft
{

	template <typename T>
	class BST_iter
	{
		public:
			typedef typename iterator_traits<T*>::iterator_category		iterator_category;
			typedef typename iterator_traits<T*>::value_type 			value_type;
			typedef typename iterator_traits<T*>::reference 			reference;
			typedef typename iterator_traits<T*>::pointer				pointer;
			typedef typename iterator_traits<T*>::difference_type		difference_type;
			typedef T													iterator_type;
			typedef const value_type*									const_pointer;
			typedef const value_type&									const_reference;
			typedef typename ft::node<value_type>						*BST_node;

		//private:

			mutable BST_node	_p;
			mutable BST_node	_first;
			mutable BST_node	_last;

		public:

			BST_iter(): _p(NULL), _first(NULL), _last(NULL) {}

			BST_iter(BST_node nd, BST_node f = NULL, BST_node l = NULL): _p(nd), _first(f), _last(l) {}

			~BST_iter() {}

			BST_iter(const BST_iter &it) : _p(it._p), _first(it._first), _last(it._last) {}

			BST_node getPtr() const
			{
				return (this->_p);
			}
			
			BST_node getf() const
			{
				return (this->_first);
			}
			
			BST_node getl() const
			{
				return (this->_last);
			}

			BST_iter &operator=(const BST_iter &other)
			{
				_p = other.getPtr();
				_first = other.getf();
				_last = other.getl();
				return (*this);
			}

			const BST_iter &operator=(const BST_iter &other) const
			{
				_p = other.getPtr();
				_first = other.getf();
				_last = other.getl();
				return *this;
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
					BST_node tmp = _p->parent;
					while (tmp != NULL && _p == tmp->right)
					{
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}

			const BST_iter &operator++() const
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
					BST_node tmp = _p->parent;
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

			const BST_iter operator++(int) const
			{
				BST_iter tmp = *this;
				++(*this);
				return (tmp);
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
					BST_node tmp = _p->parent;
					while (tmp != NULL && _p == tmp->left)
					{
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}

			const BST_iter &operator--() const
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
					BST_node tmp = _p->parent;
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

			value_type *operator->()
			{
				return (&(_p->data));
			}

			const value_type *operator->() const
			{
				return (&(_p->data));
			}

			value_type &operator*()
			{
				return (static_cast<BST_node>(_p)->data);
			}

			const value_type &operator*()const
			{
				return (static_cast<BST_node>(_p)->data);
			}

			// friend bool operator==(const BST_iter<key_type, mapped_type, Compare, Allocator> &lhs, const BST_iter<key_type, mapped_type, Compare, Allocator> &rhs)
			// {
			// 	return (lhs.getPtr() == rhs.getPtr());
			// }

			// friend bool operator!=(const BST_iter<key_type, mapped_type, Compare, Allocator> &lhs, const BST_iter<key_type, mapped_type, Compare, Allocator> &rhs)
			// {
			// 	return (!(lhs.getPtr() == rhs.getPtr()));
			// }
	};
	
	template<typename A, typename B>
	bool operator==(const BST_iter<A> &lhs, const BST_iter<B> &rhs)
	{
		return (lhs.getPtr() == rhs.getPtr());
	}

	template<typename A, typename B>
	bool operator!=(const BST_iter<A> &lhs, const BST_iter<B> &rhs)
	{
		return (!(lhs.getPtr() == rhs.getPtr()));
	}

	template <typename T>
	class reverse_BST_iter
	{
		public:
			typedef typename iterator_traits<T*>::iterator_category		iterator_category;
			typedef typename iterator_traits<T*>::value_type 			value_type;
			typedef typename iterator_traits<T*>::reference 			reference;
			typedef typename iterator_traits<T*>::pointer				pointer;
			typedef typename iterator_traits<T*>::difference_type		difference_type;
			typedef T													iterator_type;
			typedef const value_type*									const_pointer;
			typedef const value_type&									const_reference;
			typedef typename ft::node<value_type>						*BST_node;

			
		private:
			mutable BST_node	_p;
			mutable BST_node	_first;
			mutable BST_node	_last;
		
		public:

			reverse_BST_iter(): _p(NULL), _first(NULL), _last(NULL) {}

			template<typename InputIterator>
			reverse_BST_iter(InputIterator first)
			{
				this->_p = first._p;
				this->_first = first._first;
				this->_last = first._last;
			}

			reverse_BST_iter(BST_node nd, BST_node f = NULL, BST_node l = NULL): _p(nd), _first(f), _last(l) {}
			
			~reverse_BST_iter() {}

			reverse_BST_iter(const reverse_BST_iter &it) : _p(it._p), _first(it._first), _last(it._last) {}

			BST_iter<T> base() const
			{
				// return (this->_p);
				BST_iter<T> it(this->_p, this->_first, this->_last);
				// return (BST_iter<T>(this->_p, this->_first, this->_last));
				return (--it);
			}

			BST_node getPtr() const
			{
				return (this->_p);
			}
			
			BST_node getf() const
			{
				return (this->_first);
			}
			
			BST_node getl() const
			{
				return (this->_last);
			}

			reverse_BST_iter &operator=(const reverse_BST_iter &other)
			{
				_p = other.getPtr();
				_first = other.getf();
				_last = other.getl();
				return (*this);
			}

			const reverse_BST_iter &operator=(const reverse_BST_iter &other) const
			{
				_p = other.getPtr();
				_first = other.getf();
				_last = other.getl();
				return (*this);
			}

			reverse_BST_iter &operator--()
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
					BST_node tmp = _p->parent;
					while (tmp != NULL && _p == tmp->right)
					{
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}

			const reverse_BST_iter &operator--() const
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
					BST_node tmp = _p->parent;
					while (tmp != NULL && _p == tmp->right)
					{
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}

			reverse_BST_iter operator++(int)
			{
				reverse_BST_iter tmp = *this;
				++(*this);
				return (tmp);
			}

			const reverse_BST_iter operator++(int) const
			{
				reverse_BST_iter tmp = *this;
				++(*this);
				return (tmp);
			}

			reverse_BST_iter &operator++()
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
					BST_node tmp = _p->parent;
					while (tmp != NULL && _p == tmp->left)
					{
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}

			const reverse_BST_iter &operator++() const
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
					BST_node tmp = _p->parent;
					while (tmp != NULL && _p == tmp->left)
					{
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}

			reverse_BST_iter operator--(int)
			{
				reverse_BST_iter tmp = *this;
				--(*this);
				return (tmp);
			}

			const reverse_BST_iter operator--(int) const
			{
				reverse_BST_iter tmp = *this;
				--(*this);
				return (tmp);
			}

			value_type *operator->()
			{
				return (&(_p->data));
			}

			const value_type *operator->() const
			{
				return (&(_p->data));
			}

			value_type &operator*()
			{
				return (static_cast<BST_node>(_p)->data);
			}

			const value_type &operator*()const
			{
				return (static_cast<BST_node>(_p)->data);
			}

			// template<typename key_type, typename mapped_type, typename Compare, typename Allocator>
			// friend bool operator==(const reverse_BST_iter<key_type, mapped_type, Compare, Allocator> &lhs, const reverse_BST_iter<key_type, mapped_type, Compare, Allocator> &rhs)
			// {
			// 	return (lhs.getPtr() == rhs.getPtr());
			// }

			// template<typename key_type, typename mapped_type, typename Compare, typename Allocator>
			// friend bool operator!=(const reverse_BST_iter<key_type, mapped_type, Compare, Allocator> &lhs, const reverse_BST_iter<key_type, mapped_type, Compare, Allocator> &rhs)
			// {
			// 	return (!(lhs.getPtr() == rhs.getPtr()));
			// }
	};
	template<typename A, typename B>
	bool operator==(const reverse_BST_iter<A> &lhs, const reverse_BST_iter<B> &rhs)
	{
		return (lhs.getPtr() == rhs.getPtr());
	}

	template<typename A, typename B>
	bool operator!=(const reverse_BST_iter<A> &lhs, const reverse_BST_iter<B> &rhs)
	{
		return (!(lhs.getPtr() == rhs.getPtr()));
	}
}

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartkow <jbartkow@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:32:21 by ben               #+#    #+#             */
/*   Updated: 2023/02/07 17:36:03 by jbartkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_HPP
# define BST_HPP

#include "iterator.hpp"
#include <cstdio>
#include "ft_map.hpp"

namespace ft
{
	template<typename value_type>
	struct node
	{
		node		*left;
		node		*right;
		node		*parent;
		value_type	data;
	};
			
	template<	typename Key,
				typename T,
				typename Compare = std::less<Key>,
				typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class BST
	{
		public:

			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef node<value_type>							_node;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef	typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

		private:

			size_type														_size;
			allocator_type													_alloc;
			typedef typename allocator_type::template rebind<node<value_type> >::other	_node_alloc;
			_node_alloc														_alloc_node;

		public:

			key_compare	_comp;
			_node		*_bst;

			BST(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _size(0), _alloc(alloc), _comp(comp), _bst(NULL) {}

			BST &operator=(const BST &other)
			{
				_size = other._size;
				_alloc = other._alloc;
				_comp = other._comp;
				_bst = other._bst;
				return (*this);
			}

			~BST() {}

			void setCompandAlloc(key_compare comp,allocator_type alloc) {_comp = comp; _alloc = alloc;}

			bool empty() const
			{
				return (this->_size == 0);
			}

			size_type size() const
			{
				return (this->_size);
			}

			_node *new_node(const value_type &value, _node *parent = NULL)
			{		
				_node *new_node = _alloc_node.allocate(1);

				_alloc.construct(&(new_node->data), value);
				new_node->left = NULL;
				new_node->right = NULL;
				new_node->parent = parent;
				if (parent)
				{
					if (this->_comp(value.first, parent->data.first))
						parent->left = new_node;
					else
						parent->right = new_node;
				}
				_size++;
				return (new_node);
			}

			void copyTree(_node *rt = NULL)
			{
				if (!rt)
					return ;
				_insert(ft::pair<key_type, mapped_type>(rt->data.first, rt->data.second));
				copyTree(rt->left);
				copyTree(rt->right);
			}

			size_type max_size() const
			{
				return (this->_alloc.max_size());
			}

			_node *getRoot() const
			{
				return (this->_bst);
			}

			_node *getToRoot() const
			{
				_node *tmp = _bst;
				while (tmp->parent)
					tmp = tmp->parent;
				return (tmp);
			}

			bool _isLeaf(_node *bst) const
			{
				return (bst->left == NULL && bst->right == NULL);
			}

			bool _isEmpty(_node *bst) const
			{
				return (bst == NULL);
			}

			void _clear(_node *nd = NULL)
			{
				if (_bst == NULL)
					return ;
				if (nd == NULL)
					nd = _bst;
				if (nd->right)
					_clear(nd->right);
				if (nd->left)
					_clear(nd->left);
				if (_isLeaf(nd))
				{
					if (nd->parent && nd->parent->right == nd)
						nd->parent->right = NULL;
					else if (nd->parent && nd->parent->left == nd)
						nd->parent->left = NULL;
					_alloc_node.deallocate(nd, 1);
				}
				if (nd == _bst)
					_bst = NULL;
				_size--;
			}

			
			_node *_findNode(const key_type &key) const
			{
				_node *res = _bst;

				for (; res != NULL && extract_key(res->data) != key;)
				{
					if (_comp(key, extract_key(res->data)))
						res = res->left;
					else
						res = res->right;
				}
				return (res);
			}

			_node *_insert(const value_type value)
			{
				if (!_bst)
				{
					_bst = new_node(value);
					return (_bst);
				}
				_node *found;
				_node *tmp;
				found = _findNode(value.first);
				if (found)
					return (found);
				tmp = NULL;
				found = _bst;
				while (found != NULL)
				{
					tmp = found;
					if (this->_comp(value.first, found->data.first)) {
						found = found->left;
					}
					else {
						found = found->right;
					}
				}
				found = new_node(value, tmp);
				if (this->_comp(value.first, tmp->data.first))
					tmp->left = found;
				else
					tmp->right = found;
				return (found);
			}
			
			void _printMap(_node *root)
			{
				if (root != NULL)
				{
					_printMap(root->left);
					std::cout << root->data.first << ":" << root->data.second << " ";
					_printMap(root->right);
				}
			}

			void _minNmax()
			{
				if (!_bst)
					return ;
				_node *min_node = minNode(_bst);
				_node *max_node = maxNode(_bst);
				std::cout << "Min node: (" << min_node->data.first << ", " << min_node->data.second << ")\n";
				std::cout << "Max node: (" << max_node->data.first << ", " << max_node->data.second << ")\n";
			}

			_node *minNode(_node *bst) const
			{
				_node *current = bst;
			
				while (current && current->left != NULL)
					current = current->left;
				return (current);
			}

			_node *maxNode(_node *bst) const
			{
				_node *current = bst;
			
				while (current && current->right != NULL)
					current = current->right;
				return (current);
			}

			void changeData(_node* &curr, const value_type &val)
			{
				_alloc.construct(&(curr->data), val);
			}

			void _deleteNode(_node *bst)
			{
				_node *tmp = NULL;
				if (!bst)
					return ;
				if (_isLeaf(bst))
					_clear(bst);
				else if (!_isLeaf(bst))
				{
					if (bst->left)
						tmp = maxNode(bst->left);
					else if (bst->right)
						tmp = minNode(bst->right); 
					changeData(bst, tmp->data);
					_deleteNode(tmp);
				}
			}

			size_type _erase(const key_type &key)
			{
				_node*	found = _findNode(key);
				if (!_bst || !found)
					return (0);
				_deleteNode(found);
				return (1);
			}

			_node*	begin(void) const
			{
				_node*	tmp = this->_bst;

				while (tmp && tmp->left)
					tmp = tmp->left;
				return (tmp);
			}

			_node*	end(void) const
			{
				_node*	tmp = this->_bst;

				while (tmp && tmp->right)
					tmp = tmp->right;
				tmp = tmp->right;
				return (tmp);
			}
			
			_node*	rbegin(void) const
			{
				_node*	tmp = this->_bst;

				while (tmp && tmp->right)
					tmp = tmp->right;
				return (tmp);
			}

			_node*	rend(void) const
			{
				_node*	tmp = this->_bst;

				while (tmp && tmp->left)
					tmp = tmp->left;
				tmp = tmp->left;
				return (tmp);
			}
	};

	template <class value>
	value extract_key(value v)
	{
		return (v);
	}

	template <class first, class second>
	first extract_key(ft::pair<first, second> pair)
	{
		return (pair.first);
	}
}

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rRedBlackTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:55:54 by jcalon            #+#    #+#             */
/*   Updated: 2022/11/02 18:38:10 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>
#include "utility.hpp"

#define RED 0
#define BLACK 1
#define DOUBLE_BLACK 2

namespace ft
{

	template <class T>
	struct RedBlackTree
	{
		struct RedBlackTree *left;
		struct RedBlackTree *right;
		struct RedBlackTree *parent;
		int color;
		T *_data;

		RedBlackTree(void) : left(NULL), right(NULL), parent(NULL), color(BLACK), _data(NULL) {}
		RedBlackTree(T *data) : left(NULL), right(NULL), parent(NULL), color(RED), _data(data) {}
		RedBlackTree(T *data, bool is_black) : left(NULL), right(NULL), parent(NULL), color(is_black), _data(data) {}
		~RedBlackTree(void) {}
	};

	// right rotate

	template <class T>
	void update_old_root_rr(ft::RedBlackTree<T> *old_root, ft::RedBlackTree<T> *new_root)
	{
		old_root->left = new_root->right;
		if (new_root->right)
			new_root->right->parent = old_root;
	}

	template <class T>
	void update_new_root_rr(ft::RedBlackTree<T> *old_root, ft::RedBlackTree<T> *new_root, ft::RedBlackTree<T> *parent)
	{
		new_root->right = old_root;
		old_root->parent = new_root;
		new_root->parent = parent;
		if (new_root->parent)
			update_parent_child(old_root, new_root);
	}

	template <class T>
	ft::RedBlackTree<T> *tree_right_rotate(ft::RedBlackTree<T> *old_root)
	{
		if (is_nil(old_root->left))
			return NULL;

		ft::RedBlackTree<T> *parent = old_root->parent;
		ft::RedBlackTree<T> *new_root = old_root->left;

		update_old_root_rr(old_root, new_root);
		update_new_root_rr(old_root, new_root, parent);
		return (new_root);
	}

	// left rotate

	template <class T>
	void update_old_root_lr(ft::RedBlackTree<T> *old_root, ft::RedBlackTree<T> *new_root)
	{
		old_root->right = new_root->left;
		if (new_root->left)
			new_root->left->parent = old_root;
	}

	template <class T>
	void update_new_root_lr(ft::RedBlackTree<T> *old_root, ft::RedBlackTree<T> *new_root, ft::RedBlackTree<T> *parent)
	{
		new_root->left = old_root;
		old_root->parent = new_root;
		new_root->parent = parent;
		if (new_root->parent)
			update_parent_child(old_root, new_root);
	}

	template <class T>
	ft::RedBlackTree<T> *tree_left_rotate(ft::RedBlackTree<T> *old_root)
	{
		if (is_nil(old_root->right))
			return NULL;

		ft::RedBlackTree<T> *parent = old_root->parent;
		ft::RedBlackTree<T> *new_root = old_root->right;

		update_old_root_lr(old_root, new_root);
		update_new_root_lr(old_root, new_root, parent);
		return (new_root);
	}

	// create node

	template <class T, class Alloc>
	void create_end_node(ft::RedBlackTree<T> **end, Alloc alloc)
	{
		*end = alloc.allocate(1);
		alloc.construct(*end, ft::RedBlackTree<T>());
		(*end)->left = NULL;
		(*end)->right = NULL;
		(*end)->_data = NULL;
		(*end)->parent = NULL;
	}

	template <typename T, class Alloc>
	ft::RedBlackTree<T> *create_nil_node(ft::RedBlackTree<T> *parent, Alloc alloc)
	{
		ft::RedBlackTree<T> *nil_node = alloc.allocate(1);
		alloc.construct(nil_node, ft::RedBlackTree<T>());
		nil_node->parent = parent;
		nil_node->left = NULL;
		nil_node->right = NULL;
		nil_node->_data = NULL;
		return (nil_node);
	}

	template <typename T, class Alloc>
	ft::RedBlackTree<T> *tree_create_node(T *new_data, Alloc alloc)
	{
		ft::RedBlackTree<T> *new_node = alloc.allocate(1);
		alloc.construct(new_node, ft::RedBlackTree<T>(new_data));
		new_node->left = create_nil_node(new_node, alloc);
		new_node->right = create_nil_node(new_node, alloc);
		return (new_node);
	}

	template <typename T, class Alloc>
	ft::RedBlackTree<T> *tree_init_root(ft::RedBlackTree<T> **nil_root, T *new_data, Alloc alloc)
	{
		ft::RedBlackTree<T> *new_node = alloc.allocate(1);
		if (!(*nil_root)->parent)
			alloc.construct(new_node, ft::RedBlackTree<T>(new_data, BLACK));
		else
			alloc.construct(new_node, ft::RedBlackTree<T>(new_data));
		new_node->left = create_nil_node(new_node, alloc);
		new_node->right = (*nil_root);
		new_node->parent = (*nil_root)->parent;
		if ((*nil_root)->parent)
			(*nil_root)->parent->right = new_node;
		(*nil_root)->parent = new_node;
		return (new_node);
	}

	template <typename T, class Alloc>
	ft::RedBlackTree<T> *tree_create_root(T *new_data, Alloc alloc)
	{
		ft::RedBlackTree<T> *new_node = alloc.allocate(1);
		alloc.construct(new_node, ft::RedBlackTree<T>(new_data, BLACK));
		new_node->left = create_nil_node(new_node, alloc);
		new_node->right = create_nil_node(new_node, alloc);
		return (new_node);
	}

	// insert data

	template <class T>
	ft::RedBlackTree<T> *get_sibling(ft::RedBlackTree<T> *node)
	{
		if (is_left_child(node->parent, node))
			return node->parent->right;
		return node->parent->left;
	}

	template <class T>
	bool sibling_is_red(ft::RedBlackTree<T> *node)
	{
		ft::RedBlackTree<T> *sibling = get_sibling(node);

		if (is_nil(sibling))
			return (false);
		if (sibling->color == RED)
			return (true);
		return (false);
	}

	template <class T>
	void recolor(ft::RedBlackTree<T> *node)
	{
		node->color = !node->color;
	}

	template <class T>
	void recolor_node_and_sibling(ft::RedBlackTree<T> *node)
	{
		recolor(node);
		recolor(get_sibling(node));
	}

	template <class T>
	void check_rules(ft::RedBlackTree<T> *node)
	{
		ft::RedBlackTree<T> *parent = node->parent;
		ft::RedBlackTree<T> *grandma = parent->parent;

		if (parent->color == BLACK)
			return;
		if (sibling_is_red(parent))
		{
			recolor_node_and_sibling(parent);
			if (is_root(grandma))
				return;
			recolor(grandma);
			return check_rules(grandma);
		}
		if (is_left_child(grandma, parent) != is_left_child(parent, node))
		{
			if (is_left_child(parent, node))
				parent = tree_right_rotate(parent);
			else
				parent = tree_left_rotate(parent);
		}
		recolor(grandma);
		recolor(parent);
		if (is_left_child(grandma, parent))
			grandma = tree_right_rotate(grandma);
		else
			grandma = tree_left_rotate(grandma);
	}

	template <class T, class Compare, class Alloc>
	void tree_insert_data_recursive(ft::RedBlackTree<T> **root, ft::RedBlackTree<T> *parent, T *data, Compare compare, Alloc alloc)
	{
		if (is_nil(*root) && (*root) == tree_end(get_root(*root)))
		{
			ft::RedBlackTree<T> *tmp = *root;
			*root = tree_create_node(data, alloc);
			(*root)->parent = parent;
			check_rules(*root);
			ft::RedBlackTree<T> *tmp_end = tree_end(get_root(*root))->parent;
			alloc.deallocate(tmp_end->right, 1);
			tmp_end->right = tmp;
			tmp->parent = tmp_end;
			return;
		}
		else if (is_nil(*root))
		{
			alloc.deallocate(*root, 1);
			*root = tree_create_node(data, alloc);
			(*root)->parent = parent;
			check_rules(*root);
			return;
		}
		if (is_equal(*data, *((*root)->_data), compare))
			return;
		if (compare(*data, *((*root)->_data)))
			return (tree_insert_data_recursive<T>(&(*root)->left, *root, data, compare, alloc));
		return (tree_insert_data_recursive<T>(&(*root)->right, *root, data, compare, alloc));
	}

	template <class T>
	void update_root(ft::RedBlackTree<T> **root)
	{
		if (is_root(*root))
			return;
		*root = get_root(*root);
	}

	template <class T, class Compare, class Alloc>
	void tree_insert_data(ft::RedBlackTree<T> **root, T *data, Compare compare, Alloc alloc)
	{
		if (*root == NULL)
		{
			*root = tree_create_root(data, alloc);
			return;
		}
		else if (is_nil(*root))
		{
			*root = tree_init_root(root, data, alloc);
			if ((*root)->parent)
				check_rules(*root);
		}
		else if (is_equal(*data, *((*root)->_data), compare))
			return;
		else if (compare(*data, *((*root)->_data)))
			tree_insert_data_recursive<T>(&(*root)->left, *root, data, compare, alloc);
		else
			tree_insert_data_recursive<T>(&(*root)->right, *root, data, compare, alloc);
		update_root(root);
	}

	// begin/end access

	template <class T>
	const ft::RedBlackTree<T> *find_begin(const ft::RedBlackTree<T> *root)
	{
		if (is_nil(root->left))
			return (root);
		return (find_begin(root->left));
	}

	template <class T>
	const ft::RedBlackTree<T> *tree_begin(const ft::RedBlackTree<T> *root)
	{
		if (!root)
			return (NULL);
		if (is_nil(root))
			return (root);
		return (find_begin(root));
	}

	template <class T>
	ft::RedBlackTree<T> *find_begin(ft::RedBlackTree<T> *root)
	{
		if (is_nil(root->left))
			return (root);
		return (find_begin(root->left));
	}

	template <class T>
	ft::RedBlackTree<T> *tree_begin(ft::RedBlackTree<T> *root)
	{
		if (!root)
			return (NULL);
		if (is_nil(root))
			return (root);
		return (find_begin(root));
	}

	template <class T>
	const ft::RedBlackTree<T> *find_end(const ft::RedBlackTree<T> *root)
	{
		if (is_nil(root->right))
			return (root->right);
		return (find_end(root->right));
	}

	template <class T>
	const ft::RedBlackTree<T> *tree_end(const ft::RedBlackTree<T> *root)
	{
		if (!root)
			return (NULL);
		if (is_nil(root))
			return (root);
		return (find_end(root));
	}

	template <class T>
	ft::RedBlackTree<T> *find_end(ft::RedBlackTree<T> *root)
	{
		if (is_nil(root->right))
			return (root->right);
		return (find_end(root->right));
	}

	template <class T>
	ft::RedBlackTree<T> *tree_end(ft::RedBlackTree<T> *root)
	{
		if (!root)
			return (NULL);
		if (is_nil(root))
			return (root);
		return (find_end(root));
	}

	// next

	template <class T>
	bool is_pre_end(const ft::RedBlackTree<T> *node)
	{
		const ft::RedBlackTree<T> *root = get_root(node);
		return (tree_end(root)->parent == node);
	}

	template <class T>
	ft::RedBlackTree<T> *find_successor_above(const ft::RedBlackTree<T> *node)
	{
		if (is_left_child(node->parent, node))
			return (node->parent);
		return (find_successor_above(node->parent));
	}

	template <class T>
	ft::RedBlackTree<T> *tree_next(const ft::RedBlackTree<T> *node)
	{
		if (!node)
			return (NULL);
		if (is_pre_end(node))
			return (node->right);
		if (is_nil(node) || is_nil(node->right))
			return (find_successor_above(node));
		else
			return (find_successor_below(node->right));
	}

	// previous

	template <class T>
	bool is_begin(const ft::RedBlackTree<T> *node)
	{
		const ft::RedBlackTree<T> *root = get_root(node);
		return (tree_begin(root) == node);
	}

	template <class T>
	ft::RedBlackTree<T> *find_predecessor_above(const ft::RedBlackTree<T> *node)
	{
		if (is_right_child(node->parent, node))
			return (node->parent);
		return (find_predecessor_above(node->parent));
	}

	template <class T>
	ft::RedBlackTree<T> *tree_previous(const ft::RedBlackTree<T> *node)
	{
		if (!node)
			return (NULL);
		if (is_begin(node))
			return (node->left);
		if (is_nil(node) || is_nil(node->left))
			return (find_predecessor_above(node));
		else
			return (find_predecessor_below(node->left));
	}

	// search element

	template <class T, class Compare>
	const T *tree_search_data(ft::RedBlackTree<T> *root, const T data_ref, Compare compare)
	{
		if (!root || is_nil(root))
			return (NULL);
		if (is_equal(data_ref, *(root->_data), compare))
			return (root->_data);
		if (compare(data_ref, *(root->_data)))
			return (tree_search_data<T>(root->left, data_ref, compare));
		return (tree_search_data<T>(root->right, data_ref, compare));
	}

	template <class T, class Compare>
	ft::RedBlackTree<T> *tree_search_node(ft::RedBlackTree<T> *root, T data_ref, Compare compare)
	{
		if (!root || is_nil(root))
			return (NULL);
		if (is_equal(data_ref, *(root->_data), compare))
			return (root);
		if (compare(data_ref, *(root->_data)))
			return (tree_search_node(root->left, data_ref, compare));
		return (tree_search_node(root->right, data_ref, compare));
	}

	// delete node

	template <class T>
	void deal_double_black(ft::RedBlackTree<T> *double_black_node);

	template <class T>
	ft::RedBlackTree<T> *get_opposite_niece(ft::RedBlackTree<T> *node, ft::RedBlackTree<T> *sibling)
	{
		if (is_left_child(node->parent, node))
			return (sibling->right);
		return (sibling->left);
	}

	template <class T>
	ft::RedBlackTree<T> *get_same_direction_niece(ft::RedBlackTree<T> *node, ft::RedBlackTree<T> *sibling)
	{
		if (is_left_child(node->parent, node))
			return (sibling->left);
		return (sibling->right);
	}

	template <class T>
	void do_opposite_rotation(ft::RedBlackTree<T> *node_to_compare, ft::RedBlackTree<T> *node_to_rotate)
	{
		if (is_left_child(node_to_compare->parent, node_to_compare))
			tree_right_rotate(node_to_rotate);
		else
			tree_left_rotate(node_to_rotate);
	}

	template <class T>
	void do_same_side_rotation(ft::RedBlackTree<T> *node_to_compare, ft::RedBlackTree<T> *node_to_rotate)
	{
		if (is_left_child(node_to_compare->parent, node_to_compare))
			tree_left_rotate(node_to_rotate);
		else
			tree_right_rotate(node_to_rotate);
	}

	template <class T>
	bool is_black_node(ft::RedBlackTree<T> *node)
	{
		return (node->color == BLACK);
	}

	template <class T>
	bool is_red_node(ft::RedBlackTree<T> *node)
	{
		return (node->color == RED);
	}

	template <class T>
	void remove_double_black(ft::RedBlackTree<T> *node)
	{
		node->color = BLACK;
	}

	template <class T>
	void swap_node_color(ft::RedBlackTree<T> *node1, ft::RedBlackTree<T> *node2)
	{
		int tmp;

		tmp = node1->color;
		node1->color = node2->color;
		node2->color = tmp;
	}

	template <class T>
	void black_sibling_case(ft::RedBlackTree<T> *double_black_node)
	{
		ft::RedBlackTree<T> *sibling = get_sibling(double_black_node);
		ft::RedBlackTree<T> *parent = double_black_node->parent;

		if (is_red_node(get_opposite_niece(double_black_node, sibling)))
		{
			swap_node_color(parent, sibling);
			get_opposite_niece(double_black_node, sibling)->color = BLACK;
			do_same_side_rotation(double_black_node, parent);
			remove_double_black(double_black_node);
		}
		else if (is_black_node(get_same_direction_niece(double_black_node, sibling)))
		{
			double_black_node->color = BLACK;
			sibling->color = RED;
			parent->color++;
			if (parent->color == DOUBLE_BLACK)
				deal_double_black(parent);
		}
		else
		{
			swap_node_color(sibling, get_same_direction_niece(double_black_node, sibling));
			do_opposite_rotation(double_black_node, sibling);
			deal_double_black(double_black_node);
		}
	}

	template <class T>
	void red_sibling_case(ft::RedBlackTree<T> *double_black_node)
	{
		ft::RedBlackTree<T> *sibling = get_sibling(double_black_node);
		ft::RedBlackTree<T> *parent = double_black_node->parent;

		swap_node_color(parent, sibling);
		if (is_left_child(parent, double_black_node))
			tree_left_rotate(parent);
		else
			tree_right_rotate(parent);
		deal_double_black(double_black_node);
	}

	template <class T>
	void deal_double_black(ft::RedBlackTree<T> *double_black_node)
	{
		if (is_root(double_black_node))
			return (remove_double_black(double_black_node));
		if (sibling_is_red(double_black_node))
			red_sibling_case(double_black_node);
		else
			black_sibling_case(double_black_node);
	}

	template <class T>
	void check_delete_rules(ft::RedBlackTree<T> *node)
	{
		if (node->color == RED)
			return;
		node->_data = NULL;
		node->color = DOUBLE_BLACK;
		deal_double_black(node);
	}

	template <class T>
	ft::RedBlackTree<T> *find_neighbor(ft::RedBlackTree<T> *node)
	{
		if (!is_nil(node->left))
			return (find_predecessor_below(node->left));
		else
			return (find_successor_below(node->right));
	}

	template <class T>
	void replace_content(ft::RedBlackTree<T> *node, ft::RedBlackTree<T> *node_to_replace)
	{
		node->_data = node_to_replace->_data;
	}

	template <class T, class Alloc>
	void delete_leaf(ft::RedBlackTree<T> *leaf, Alloc alloc)
	{
		alloc.deallocate(leaf->right, 1);
		alloc.deallocate(leaf->left, 1);
		alloc.deallocate(leaf, 1);
	}

	template <class T, class Alloc>
	void delete_node(ft::RedBlackTree<T> *node, Alloc alloc)
	{
		check_delete_rules(node);
		if (is_left_child(node->parent, node))
			node->parent->left = create_nil_node(node->parent, alloc);
		else
			node->parent->right = create_nil_node(node->parent, alloc);
		delete_leaf(node, alloc);
	}

	template <class T, class Alloc>
	void tree_delete_recursive(ft::RedBlackTree<T> *node_to_delete, Alloc alloc)
	{
		if (is_leaf(node_to_delete))
			return (delete_node(node_to_delete, alloc));
		ft::RedBlackTree<T> *node_to_replace = find_neighbor(node_to_delete);
		replace_content(node_to_delete, node_to_replace);
		return (tree_delete_recursive(node_to_replace, alloc));
	}

	template <class T, class Compare, class Alloc>
	T *tree_delete(ft::RedBlackTree<T> **root, T data_ref, Compare compare, Alloc alloc)
	{
		ft::RedBlackTree<T> *node_to_delete = tree_search_node(*root, data_ref, compare);
		if (!node_to_delete)
			return (NULL);
		const T *data_to_return = node_to_delete->_data;
		if (is_last_node(node_to_delete))
		{
			delete_leaf(node_to_delete, alloc);
			*root = NULL;
		}
		else
		{
			tree_delete_recursive(node_to_delete, alloc);
			update_root(root);
		}
		return (const_cast<T *>(data_to_return));
	}

	// utils

	template <class T, class Compare>
	bool is_equal(const T &data1, const T &data2, Compare compare)
	{
		if (compare(data1, data2))
			return (false);
		if (compare(data2, data1))
			return (false);
		return (true);
	}

	template <class T>
	bool is_nil(const ft::RedBlackTree<T> *node)
	{
		if (!node->_data && !node->left && !node->right)
			return (true);
		return (false);
	}

	template <class T>
	ft::RedBlackTree<T> *find_successor_below(ft::RedBlackTree<T> *node)
	{
		if (is_nil(node->left))
			return (node);
		return (find_successor_below(node->left));
	}

	template <class T>
	ft::RedBlackTree<T> *find_predecessor_below(ft::RedBlackTree<T> *node)
	{
		if (is_nil(node->right))
			return (node);
		return (find_predecessor_below(node->right));
	}

	template <class T>
	ft::RedBlackTree<T> *get_root(ft::RedBlackTree<T> *node)
	{
		ft::RedBlackTree<T> *tmp = node;

		while (tmp->parent)
			tmp = tmp->parent;
		return (tmp);
	}

	template <class T>
	const ft::RedBlackTree<T> *get_root(const ft::RedBlackTree<T> *node)
	{
		const ft::RedBlackTree<T> *tmp = node;

		while (tmp->parent)
			tmp = tmp->parent;
		return (tmp);
	}

	template <class T>
	bool is_root(const ft::RedBlackTree<T> *node)
	{
		return (node->parent == NULL);
	}

	template <class T>
	bool is_left_child(const ft::RedBlackTree<T> *parent, const ft::RedBlackTree<T> *node)
	{
		return (parent->left == node);
	}

	template <class T>
	bool is_right_child(const ft::RedBlackTree<T> *parent, const ft::RedBlackTree<T> *node)
	{
		return (parent->right == node);
	}

	template <class T>
	bool is_leaf(const ft::RedBlackTree<T> *node)
	{
		if (is_nil(node->left) && is_nil(node->right))
			return (true);
		return (false);
	}

	template <class T>
	bool is_last_node(const ft::RedBlackTree<T> *node)
	{
		return (is_root(node) && is_leaf(node));
	}

	template <class T>
	bool node_to_rotate_was_parent_left_child(ft::RedBlackTree<T> *parent, ft::RedBlackTree<T> *node_to_rotate)
	{
		return (parent->left == node_to_rotate);
	}

	template <class T>
	void update_parent_child(ft::RedBlackTree<T> *node_to_rotate, ft::RedBlackTree<T> *new_root)
	{
		if (node_to_rotate_was_parent_left_child(new_root->parent, node_to_rotate))
			new_root->parent->left = new_root;
		else
			new_root->parent->right = new_root;
	}

} // ft

#endif
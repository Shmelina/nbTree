#ifndef TREE_H
#define TREE_H

#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

template <class _DT>
class tree_node
{
private:
	vector<tree_node*> _child_node;
	_DT _node_data;
public:
	tree_node(const _DT& Node_data) :_node_data(Node_data) {}
	tree_node(_DT&& Node_data) :_node_data(Node_data) {}
	~tree_node()
	{
		for (auto& i : _child_node)
		{
			i->~tree_node();
			delete i;
		}
	}
	_DT child_pop_back()
	{
		return _child_node.pop_back();
	}
	bool children_empty()
	{
		return (_child_node.size() == 0);
	}
	size_t children_size()
	{
		return _child_node.size();
	}
	void set_node(_DT Node_data)
	{
		_node_data = Node_data;
	}
	void add_child(_DT _child)
	{
		_child_node.push_back(new tree_node(_child));
	}
	/*void add_child(_DT name)
	{
		child.push_back(leaf(level + 1, name));
		lex = NULL;
	}*/
	tree_node& get_child(int i)
	{
		if (i < _child_node.size() && i >= 0)
			return _child_node[i];
	}
	_DT get_node_data()
	{
		return _node_data;
	}
	/*leaf& get_child_by_lexem(_DT )
	{
		for (auto& i : child)
		{
			if (i.get_lexem().get_name() == lexem_name)
				return i;
			else
				i.get_child_by_lexem(lexem_name);
		}
	}*/
	/*bool search_for_data(_DT Data)
	{
		for (auto& i : _child_node)
		{
			if (i.get_lexem().get_name() == Data)
				return true;
			else
				i.search_for_lexem_name(Data);
		}
		return false;
	}*/
	tree_node& operator[](int _indx)
	{
		return *_child_node[_indx];
	}
	const tree_node operator[](int _indx) const
	{
		return _child_node[_indx];
	}
	void operator=(_DT _obj)
	{
		_node_data = _obj;
	}
	bool operator==(_DT _obj)
	{
		return _node_data == _obj;
	}
	void operator+=(_DT _obj)
	{
		this->add_child(_obj);
	}
//private:
	void print_to_stream(ostream& output,
		int level,
		string indent, string pre, char post) const
	{
		for (int i = 0; i < level; i++)
			output << indent;
		output << pre << _node_data << post;
		for (const auto& i : _child_node)
			i->print_to_stream(output, 1 + level, indent, pre, post);
	}
};

template <class _Tree_type>
class tree
{
private:
	tree_node<_Tree_type>* _Head;
public:
	tree() :_Head(nullptr) {};
	tree(_Tree_type& Head) : _Head(Head) {};
	tree(const _Tree_type Head) :_Head(Head) {};
	~tree()
	{
		_Head->~tree_node();
	}
	tree_node<_Tree_type>& operator[](int _indx)
	{
		return *_Head[_indx];
	}
	const tree_node<_Tree_type> operator[](int _indx) const
	{
		return  _Head[_indx];
	}
	void operator=(_Tree_type _obj)
	{
		_Head = _obj;
	}
	bool operator==(_Tree_type _obj)
	{
		return _Head == _obj;
	}
	void operator+=(_Tree_type _obj)
	{
		new _Head(_obj);
		//_Head->add_child(_obj);
	}
	template<typename ValTy>
	friend ostream& operator<<(ostream&, const tree<ValTy>&);
};

template<typename ValTy>
ostream& operator<<(ostream& stream, tree<ValTy>& instance) {
	instance._Head.print_to_stream(stream, 0, "|   ", "|-->", '\n');
	return stream;
}
#endif // TREE_H

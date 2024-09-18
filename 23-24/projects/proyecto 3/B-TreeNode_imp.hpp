#pragma once
#include "B-TreeNode.hpp"
#include <iostream>

template <class T>
BTreeNode<T>::BTreeNode(int degree, NodeType type)
{
    assert(degree > 2);

    left_over_ = nullptr;
    parent_ = nullptr;

    node_type_ = type;

    degree_ = degree;
    size_ = 0;
}

template <class T>
std::vector<typename BTreeNode<T>::EntryRef>& BTreeNode<T>::entries()
{
    return entries_;
}

template <class T>
std::vector<typename BTreeNode<T>::EntryRef>& BTreeNode<T>::entries() const
{
    return entries_;
}

template <class T>
typename BTreeNode<T>::EntryRef 
BTreeNode<T>::entry(size_t index) const
{
    return entries().at(index);
}

template <class T>
typename BTreeNode<T>::Ref 
BTreeNode<T>::child(size_t index) const
{
    return entry(index)->child();    
}

template <class T>
typename BTreeNode<T>::Ref 
BTreeNode<T>::left_over() const
{
    return left_over_;
}

template <class T>
typename BTreeNode<T>::Ref 
BTreeNode<T>::parent() const
{
    return parent_;
}

template <class T>
typename BTreeNode<T>::NodeType 
BTreeNode<T>::node_type() const
{
    return node_type_;
}

template <class T>
int BTreeNode<T>::degree() const
{
    return degree_;
}

template <class T>
int BTreeNode<T>::size() const
{
    return size_;
}

template <class T>
bool BTreeNode<T>::set_entry(size_t index, EntryRef new_entry)
{
    bool in_bound = index < size_t(entries().size()); 

    if (in_bound){entries()[index] = new_entry;}

    return in_bound;
}


template <class T>
bool BTreeNode<T>::set_child(size_t index, Ref new_child)
{
    bool in_bound = index < entries().size(); 

    if (in_bound){entries().at(index)->set_child(new_child);}

    return in_bound;
}

template <class T>
void BTreeNode<T>::set_left_over(Ref new_left_over)
{
    left_over_ = new_left_over;
}

template <class T>
void BTreeNode<T>::set_parent(Ref new_parent)
{
    parent_ = new_parent;
}

template <class T>
void BTreeNode<T>::set_node_type(NodeType new_type)
{
    node_type_ = new_type;
}

template <class T>
bool BTreeNode<T>::is_full() const
{
    return degree() == size();
}

template <class T>
bool BTreeNode<T>::is_empty() const
{
    return size() == 0;
}

template <class T>
void BTreeNode<T>::insert(T key)
{
    assert(node_type() == NodeType::ROOT || size() >= std::floor((degree() - 1)/2));
    assert(size() < degree());

    auto new_entry = BTreeEntry<T>::create(key,nullptr);

    auto comp = [](const BTreeNode<T>::EntryRef &a, const BTreeNode<T>::EntryRef &b)
    {
        if (a->is_empty() && b->is_empty()) return false;
        else if (!a->is_empty() && b->is_empty()) return true;
        else if (a->is_empty() && !b->is_empty()) return false;
        else return a->key() < b->key();     
    };

    const auto &it = std::lower_bound(entries().begin(),entries().end(),new_entry,comp);

    entries().insert(it,new_entry);

    
    size_++;
}

template <class T>
void BTreeNode<T>::split()
{

}


template <class T>
std::ostream& BTreeNode<T>::fold(std::ostream& os, const std::string& prefix, bool is_tail) const {
    for (size_t i = 0; i < entries_.size(); ++i) 
    {
        const auto& entry = entries_[i];
        if (i == entries_.size() - 1) 
        {
            os << prefix << (is_tail ? "└── " : "├── ") << entry->key() << std::endl;
            if (entry->child()) 
            {
                entry->child()->fold(os, prefix + (is_tail ? "    " : "│   "), true);
            }
        } 
        else 
        {
            os << prefix << (is_tail ? "└── " : "├── ") << entry->key() << std::endl;
            if (entry->child()) 
            {
                entry->child()->fold(os, prefix + (is_tail ? "    " : "│   "), false);
            }
        }
    }
    return os;
}


#pragma once
#include "B-TreeEntry.hpp"

template <class T>
BTreeEntry<T>::BTreeEntry(T key, NodeRef child)
{
    entry_ = std::make_shared<std::pair<T, NodeRef>>(key, child);
}

template <class T>
BTreeEntry<T>::BTreeEntry()
{
    entry_ = nullptr;
}

template <class T>
T BTreeEntry<T>::key() const 
{
    return entry_->first;
}

template <class T>
typename BTreeEntry<T>::NodeRef BTreeEntry<T>::child() const 
{
    return entry_->second;
}

template <class T>
typename BTreeEntry<T>::PairRef BTreeEntry<T>::entry() const
{
    return entry_;
}

template <class T>
void BTreeEntry<T>::set_key(const T new_key)
{
    entry()->first = new_key;
}

template <class T>
void BTreeEntry<T>::set_child(const NodeRef  new_child)
{
    entry()->second = new_child;
}

template <class T>
void BTreeEntry<T>::set_entry(const T new_key, const NodeRef new_child)
{
    entry_ = PairRef({new_key,new_child});
}

template <class T>
bool BTreeEntry<T>::is_empty() const 
{
    return entry() == nullptr;
}

template <class T>
bool BTreeEntry<T>::has_child() const
{
    return child() != nullptr;
}

template <class T>
typename BTreeEntry<T>::Ref BTreeEntry<T>::create(T key, NodeRef child) 
{
    return std::make_shared<BTreeEntry<T>>(key, child);
}

template <class T>
typename BTreeEntry<T>::Ref BTreeEntry<T>::create()
{
    return std::make_shared<BTreeEntry<T>>();
}
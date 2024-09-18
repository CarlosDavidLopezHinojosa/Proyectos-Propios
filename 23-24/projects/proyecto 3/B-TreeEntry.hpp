#pragma once
#include "B-TreeNode.hpp"


template<class T>
class BTreeEntry 
{
    public:
    using NodeRef = typename BTreeNode<T>::Ref;
    using Ref = std::shared_ptr<BTreeEntry<T>>;
    using PairRef = std::shared_ptr<std::pair<T, NodeRef>>;

    BTreeEntry(T key, NodeRef child = nullptr);

    BTreeEntry();

    ~BTreeEntry(){}

    T key() const;

    NodeRef child() const;

    PairRef entry() const;

    void set_key(const T new_key);

    void set_child(const NodeRef new_child);

    void set_entry(const T new_key, const NodeRef new_child);

    bool is_empty() const;

    bool has_child() const;
 
    static Ref create(T key, NodeRef child = nullptr);

    static Ref create();

    protected:
    PairRef entry_;
};

#include "B-TreeEntry_imp.hpp"

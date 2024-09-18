#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <utility>

// Declaración adelantada de BTreeEntry
template <class T>
class BTreeEntry;

// Se debe cumplir que size() == floor((degree - 1) / 2), excepto para el root
template <class T>
class BTreeNode 
{
public:
    using Ref = std::shared_ptr<BTreeNode<T>>;
    using EntryRef = std::shared_ptr<BTreeEntry<T>>;

    enum NodeType {ROOT = 0, INNER = 1, LEAF = 2};

    BTreeNode(int degree, NodeType type = NodeType::ROOT);

    ~BTreeNode(){}

    std::vector<EntryRef>& entries();

    std::vector<EntryRef>& entries() const;

    EntryRef entry(size_t index) const;

    Ref child(size_t index) const;

    Ref left_over() const;

    Ref parent() const;

    NodeType node_type() const;

    int degree() const;

    int size() const;

    bool set_entry(size_t index, EntryRef new_entry = nullptr);

    bool set_child(size_t index, Ref new_child = nullptr);

    void set_left_over(Ref new_left_over);

    void set_parent(Ref new_parent);

    void set_node_type(NodeType new_type);

    bool is_full() const;

    bool is_empty() const;

    void insert(T key);

    void split();

    std::ostream& fold(std::ostream& os, const std::string& prefix = "", bool is_tail = true) const;

protected:
    std::vector<EntryRef> entries_;
    Ref left_over_;
    Ref parent_;

    NodeType node_type_;

    int degree_;
    int size_;
};

#include "B-TreeNode_imp.hpp"
#include "B-TreeEntry.hpp"

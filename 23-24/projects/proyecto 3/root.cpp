#include "B-TreeNode.hpp"
#include <iostream>

int main ()
{
    BTreeNode<int> node(3);
    

    node.insert(3);
    node.insert(5);


    node.child(0)->insert(10);
    node.child(0)->insert(7);


    
    node.fold(std::cout);
}
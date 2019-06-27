#include "BTree.h"



int main()
{
    BTreeNode<int, void*, 4> node;
    node.SplitChild(0);
    return 0;
}
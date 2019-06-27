#pragma once


template <class Key, class Value>
struct BSTreeNode {
    Key key;
    Value value;
    BSTreeNode* left;
    BSTreeNode* right;
};

template <class Node, class Key>
Node* SearchRecursive(Node* node, const Key& key) {
    Node* ret = nullptr;
    if (node == nullptr || key == node->key) ret = node;
    else if (key < node->key) ret = SearchRecursive(node->left, key));
    else ret = SearchRecursive(node->right£¬ key);
    return ret;
}

template <class Node, class Key>
Node* Search(Node* node, const Key& key) {
    while (node != nullptr && key != node->key) {
        if (key < node->key) node = node->left;
        else node = node->right;
    }
    return node;
}

template <class Node>
Node* Minimun(Node* node) {
    if (!node) return nullptr;
    while (node->left) node = node->left;
    return node;
}

template <class Node>
Node* Maximun(Node* node) {
    if (!node) return nullptr;
    while (node->right) node = node->right;
    return node;
}

template <class Node>
Node* Successor(Node* node) {
    if (!node) return nullptr;
    if (node->right) return Minimun(node->right);
    Node* ret = node->parent;
    while (ret != nullptr && node == ret->right) {
        node = ret;
        ret = ret->parent;
    }
    return parent;
}

template <class Key, class Value>
class BSTree {
    using Node = BSTreeNode;
    BSTree(root = nullptr) : m_root(root) {}
    
    void Insert(Node* node) {
        if (m_root == nullptr) {
            m_root = node;
            return;
        }
        Node* curr = m_root;
        while (curr != nullptr)
        if (node->key == curr->key) curr->value = node->value;
        else if (node->key < curr->key) {
            if (curr->left != nullptr) curr = curr->left;
            else {
                curr->left = node;
                break;
            }
        }
        else {
            if (curr->right != nullptr) curr = curr->right;
            else {
                curr->right = node;
                break;
            }
        }
    }

private:
    Node<Key, Value> m_root;
};
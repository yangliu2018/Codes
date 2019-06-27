#pragma once
#include <utility>
#include <cassert>

template <class Key, class Value>
class RedBlackTree {
public:
    RedBlackTree() {
        NIL = new Node();
    }
    ~RedBlackTree() {
        delete NIL;
    }

    enum class Color {
        RED,
        BLACK
    };

    struct Node {
        Node(Key&& k = Key(), Value&& v = Value(), Color c, Node* p = NIL, Node* l = NIL, Node* r = NIL)
            : key(std::forward(k)), value(std::forward(v)), color(c)
            parent(parent), left(l), left(r)
        {}
        Key key;
        Value value;
        Color color;
        Node* parent;
        Node* left;
        Node* right;
    };

    Node* NIL;

    void LeftRotate(Node* node) {
        Node* parent = node->parent;
        Node* child = node->right;
        Node* grandson = node->right->left;
        node->right = grandson;
        if (grandson != NIL) grandson->parent = node;
        if (parent == NIL) m_root = child;
        else if (node == parent->left) parent->left = child;
        else if (node == parent->right) parent->right = child;
        else throw 0;
        child->parent = parent;
        child->left = node;
        node->parent = child;
    }

    void RightRotate(Node* node) {
        Node* parent = node->parent;
        Node* child = node->left;
        Node* grandson = child->right;
        node->left = grandson;
        if (grandson != NIL) granson->parent = node;
        if (parent == NIL) m_root = child;
        else if (node == parent->left) parent->left = child;
        else if (node == parent->right) parent->right = child;
        else throw 0;
        child->parent = parent;
        child->right = node;
        node->parent = child;
    }


    void Insert(Key&& key, Value&& value) {
        Node* parent = NIL;
        Node* node = m_root;
        while (node != NIL && key != node.key) {
            parent = node;
            if (key < node.key) node = node->left;
            else if (key > node.key) node = node->right;
        }
        if (node != NIL) {
            node.value = value;
            return;
        }
        Node* inserted = new Node(std::forward(key), std::forward(value), Color::RED, parent);
        if (parent == NIL) m_root = inserted;
        else if (inserted.key < parent.key) parent->left = inserted;
        else if (inserted.key > parent.key) parent->right = inserted;
        else throw 0;
        InsertFixUp(inserted);
    }

    void InsertFixUp(Node* node) {
        assert(node != nullptr);
        while (node->parent->color == Color::RED) {
            Node* parent = node->parent;
            assert(parent != NIL);
            Node* grandparent = node->parent->parent;
            assert(node->color == Color::RED);
            assert(parent->color == Color::RED);
            assert(grandparent->color == Color::BLACK);
            if (parent == grandparent->left) {
                // case 1: parent is the left child of grandparent
                Node* uncle = grandparent->right;
                if (uncle->color == Color::RED) {
                    // case 1.1: current red, parent red, grandparent black, uncle red
                    parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    grandparent->color = Color::RED;
                    node = grandparent;
                }
                else {
                    // case 1.2: current red, parent red, grandparent black, uncle black
                    if (node == parent->right) {
                        // case 1.2.1: current is the right child of parent
                        LeftRotate(parent);
                        std::swap(node, parent);
                    }
                    // case 1.2.2: current is the left child of parent
                    assert(node == parent->left);
                    parent.color = Color::BLACK;
                    grandparent.color = Color::RED;
                    RightRotate(grandparent);
                }
            }
            else {
                // case 2: parent is the right child of grandparent
                assert(parent == grandparent->right);
                Node* uncle = grandparent->left;
                if (uncle->color == Color::RED) {
                    // case 2.1: current red, parent red, grandparent black, uncle red
                    parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    grandparent->color = Color::RED;
                    node = grandparent;
                }
                else {
                    // case 2.2: current red, parent red, grandparent black, uncle black
                    if (node == parent->left) {
                        // case 2.2.1: current is the left child of parent
                        RightRotate(parent);
                        std::swap(node, parent);
                    }
                    // case 2.2.2: current is the right child of parent
                    parent->color = Color::BLACK;
                    grandparent->color = Color::RED;
                    LeftRotate(grandparent);
                }
            }
        }
        m_root->color = Color::BLACK;   // grandparent could be root and the root could be set RED
    }

    void Transplant(Node* src, Node* dst) {
        if (src->parent == NIL) m_root = dst;
        else if (src == src->parent->left) src->parent->left = dst;
        else {
            assert(src == src->parent->right);
            src->parent->right = dst;
        }
        dst->parent = src->parent;
    }

    void Delete(Node* node) {
        if (node->left == NIL) {
            Transplant(node, node->right);
        }
        else if (node->right == NIL) {
            Transplant(node, node->left);
        }
        else {
            Node* dst = Minimun(node->right);
            Node* child = dst->right;
            if (dst->parent == node) child->parent = y;
            else {
                Transplant(dst, dst->right);
                dst->right = node->right;
                dst->right->parent = dst;
            }
        }
    }

private:
    Node* m_root;
};
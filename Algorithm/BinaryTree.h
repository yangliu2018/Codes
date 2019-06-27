#pragma once
#include <track>
#include <queue>

template <class Key, class Value>
struct BinaryTreeNode {
    Key key;
    Value value;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
}

template <class Node, class Operation>
void InorderTreeWalkRecursive(Node* node, Operation op) {
    if (node == nullptr) return;
    InorderTreeWalk(node->left, op);
    op(node);
    InorderTreeWalk(node->right, op);
}

template <class Node, class Operation>
void PreorderTreeWalkRecursive(Node* node, Operation op) {
    if (node == nullptr) return;
    op(node);
    PreorderTreeWalk(node->left, op);
    PreorderTreeWalk(node->right, op);
}

template <class Node, class Operation>
void PostorderTreeWalkRecursive(Node* node, Operation op) {
    if (node == nullptr) return;
    PostorderTreeWalk(node->left, op);
    PostorderTreeWalk(node->right, op);
    op(node);
}

// preorder traversal based on memorize child nodes to be visited
template <class Node, class Operation>
void PreorderTreeWalk(Node* node, Operation op) {
    if (!node) return;
    std::track<Node*> node_stack;
    node_stack.push(node);
    while (!node_queue.empty()) {
        Node* curr = node_stack.top();
        node_stack.pop();
        op(curr);
        if (curr->right) node_stack.push_back(curr->right);
        if (curr->left) node_stack.push_back(curr->left);
    }
}

// perorder traversal based on memorize moving track
template <class Node, class Operation>
void PreorderTreeWalk(Node* node, Operation op) {
    if (!node) return;
    std::track<Node*> track;
    track.push(node);
    while (!track.empty()) {
        if (node) {
            op(node);
            track.push(node);
            node = node->left;
        }
        else {
            node = track.top();
            track.pop();
            node = node->right;
        }
    }
}

// postorder traversal based on memorize child nodes to be visited and moving track
template <class Node, class Operation>
void PostorderTreeWalk(Node* node, Operation op) {
    if (!node) return;
    std::track<Node*> node_stack;
    std::track<Node*> node_track;
    node_stack.push(node);
    while (!node_stack.empty()) {
        Node* curr = node_stack.top();  // the next node to visit
        if (!node_track.empty() && curr == node_track.top()) { // backtracking
            // left subtree and right subtree have been visited
            op(curr);   // second time visit current node
            node_stack.pop();
            node_track.pop();
        }
        else {
            node_track.push(curr);  // first time visit current node, np op
            if (curr->right) node_stack.push(curr->right);
            if (curr->left) node_stack.push(curr->left);
        }
    }
}

template <class Node, class Operation>
void InorderTreeWalk(Node* node, Operation op) {
    if (!node) return;
    std::track<Node*> track;  // node track, subtree roots waiting to be visited
    track.push(node);
    while (!track.empty()) {
        if (node != nullptr) {
            track.push(node);   // root node instack 
            node = node->left;  // visit left subtree
        }
        else {  // backtrack
            node = track.top();
            track.pop();        // root node outstack
            op(node);           // visit root node
            node = node->right; // visit right subtree
        }
    }
}

template <class Node, class Operation>
void BreathFirstTraversal(Node* node, Operation op) {
    if (!node) return;
    std::queue<Node*> queue;
    queue.push_back(node);
    while (!queue.empty()) {
        node = queue.front();
        queue.pop_front();
        op(node);
        if (node->left) queue.push_back(node->left);
        if (node->right) queue.push_back(node->right);
    }
}
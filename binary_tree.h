#pragma once

#include <memory>
#include <queue>
#include <vector>

class BinaryTree {
private:
    struct Node {
        int value;
        int count;  // handle duplicate values
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(int v) : value(v), count(1) {}
    };

    std::unique_ptr<Node> root;

    static void insert(std::unique_ptr<Node>& node, int value) {
        if (!node) {
            node = std::make_unique<Node>(value);
            return;
        }

        if (value < node->value) {
            insert(node->left, value);
        } else if (value > node->value) {
            insert(node->right, value);
        } else {
            ++node->count;
        }
    }

    static bool contains(const Node* node, int value) {
        if (!node) return false;
        if (value < node->value) return contains(node->left.get(), value);
        if (value > node->value) return contains(node->right.get(), value);
        return true;
    }

    static void inorder(const Node* node, std::vector<int>& out) {
        if (!node) return;
        inorder(node->left.get(), out);
        for (int i = 0; i < node->count; ++i) out.push_back(node->value);
        inorder(node->right.get(), out);
    }

    static void preorder(const Node* node, std::vector<int>& out) {
        if (!node) return;
        for (int i = 0; i < node->count; ++i) out.push_back(node->value);
        preorder(node->left.get(), out);
        preorder(node->right.get(), out);
    }

    static void postorder(const Node* node, std::vector<int>& out) {
        if (!node) return;
        postorder(node->left.get(), out);
        postorder(node->right.get(), out);
        for (int i = 0; i < node->count; ++i) out.push_back(node->value);
    }

public:
    void insert(int value) { insert(root, value); }

    [[nodiscard]] bool contains(int value) const { return contains(root.get(), value); }

    [[nodiscard]] bool empty() const { return root == nullptr; }

    [[nodiscard]] std::vector<int> inorder() const {
        std::vector<int> out;
        inorder(root.get(), out);
        return out;
    }

    [[nodiscard]] std::vector<int> preorder() const {
        std::vector<int> out;
        preorder(root.get(), out);
        return out;
    }

    [[nodiscard]] std::vector<int> postorder() const {
        std::vector<int> out;
        postorder(root.get(), out);
        return out;
    }

    [[nodiscard]] std::vector<int> levelOrder() const {
        std::vector<int> out;
        if (!root) return out;

        std::queue<const Node*> q;
        q.push(root.get());

        while (!q.empty()) {
            const Node* cur = q.front();
            q.pop();

            for (int i = 0; i < cur->count; ++i) out.push_back(cur->value);

            if (cur->left) q.push(cur->left.get());
            if (cur->right) q.push(cur->right.get());
        }

        return out;
    }
};

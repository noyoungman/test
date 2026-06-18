#include <cassert>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

class BinaryTree {
public:
    enum class Order { Inorder, Preorder, Postorder };

private:
    struct Node {
        int value;
        int count;  // handle duplicate values
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(int v) : value(v), count(1) {}
    };

    std::unique_ptr<Node> root;

    static void emitValues(const Node* node, std::vector<int>& out) {
        for (int i = 0; i < node->count; ++i) out.push_back(node->value);
    }

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

    static void traverse(const Node* node, std::vector<int>& out, Order order) {
        if (!node) return;
        if (order == Order::Preorder) emitValues(node, out);
        traverse(node->left.get(), out, order);
        if (order == Order::Inorder) emitValues(node, out);
        traverse(node->right.get(), out, order);
        if (order == Order::Postorder) emitValues(node, out);
    }

public:
    void insert(int value) { insert(root, value); }

    [[nodiscard]] bool contains(int value) const { return contains(root.get(), value); }

    [[nodiscard]] bool empty() const { return root == nullptr; }

    [[nodiscard]] std::vector<int> traverse(Order order) const {
        std::vector<int> out;
        traverse(root.get(), out, order);
        return out;
    }

    [[nodiscard]] std::vector<int> inorder() const { return traverse(Order::Inorder); }
    [[nodiscard]] std::vector<int> preorder() const { return traverse(Order::Preorder); }
    [[nodiscard]] std::vector<int> postorder() const { return traverse(Order::Postorder); }

    [[nodiscard]] std::vector<int> levelOrder() const {
        std::vector<int> out;
        if (!root) return out;

        std::queue<const Node*> q;
        q.push(root.get());

        while (!q.empty()) {
            const Node* cur = q.front();
            q.pop();

            emitValues(cur, out);

            if (cur->left) q.push(cur->left.get());
            if (cur->right) q.push(cur->right.get());
        }

        return out;
    }
};

static void printVector(const char* label, const std::vector<int>& values) {
    std::cout << label;
    for (int v : values) std::cout << v << ' ';
    std::cout << '\n';
}

int main() {
    BinaryTree tree;
    assert(tree.empty());

    const int values[] = {8, 3, 10, 1, 6, 14, 4, 7, 13, 6, 3};
    for (int v : values) tree.insert(v);

    assert(!tree.empty());
    assert(tree.contains(7));
    assert(tree.contains(6));
    assert(!tree.contains(99));

    const auto in = tree.inorder();
    const auto pre = tree.preorder();
    const auto post = tree.postorder();
    const auto level = tree.levelOrder();

    assert((in == std::vector<int>{1, 3, 3, 4, 6, 6, 7, 8, 10, 13, 14}));
    assert(pre.size() == in.size());
    assert(post.size() == in.size());
    assert(level.size() == in.size());

    printVector("Inorder: ", in);
    printVector("Preorder: ", pre);
    printVector("Postorder: ", post);
    printVector("Level order: ", level);

    return 0;
}

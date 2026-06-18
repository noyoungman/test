#include "binary_tree.h"

#include <cassert>
#include <iostream>
#include <vector>

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

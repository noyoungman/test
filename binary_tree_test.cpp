#include "binary_tree.h"

#include <gtest/gtest.h>
#include <vector>

// ---------------------------------------------------------------------------
// Empty tree
// ---------------------------------------------------------------------------

TEST(BinaryTreeTest, EmptyTreeIsEmpty) {
    BinaryTree tree;
    EXPECT_TRUE(tree.empty());
}

TEST(BinaryTreeTest, EmptyTreeContainsNothing) {
    BinaryTree tree;
    EXPECT_FALSE(tree.contains(0));
    EXPECT_FALSE(tree.contains(42));
    EXPECT_FALSE(tree.contains(-1));
}

TEST(BinaryTreeTest, EmptyTreeTraversalsReturnEmpty) {
    BinaryTree tree;
    EXPECT_TRUE(tree.inorder().empty());
    EXPECT_TRUE(tree.preorder().empty());
    EXPECT_TRUE(tree.postorder().empty());
    EXPECT_TRUE(tree.levelOrder().empty());
}

// ---------------------------------------------------------------------------
// Single element
// ---------------------------------------------------------------------------

TEST(BinaryTreeTest, SingleElement) {
    BinaryTree tree;
    tree.insert(5);

    EXPECT_FALSE(tree.empty());
    EXPECT_TRUE(tree.contains(5));
    EXPECT_FALSE(tree.contains(4));
    EXPECT_FALSE(tree.contains(6));

    EXPECT_EQ(tree.inorder(), std::vector<int>({5}));
    EXPECT_EQ(tree.preorder(), std::vector<int>({5}));
    EXPECT_EQ(tree.postorder(), std::vector<int>({5}));
    EXPECT_EQ(tree.levelOrder(), std::vector<int>({5}));
}

// ---------------------------------------------------------------------------
// Preorder – exact output verification (previously only size-checked)
// ---------------------------------------------------------------------------

TEST(BinaryTreeTest, PreorderExactValues) {
    //       8
    //      / \
    //     3   10
    //    / \    \
    //   1   6   14
    //      / \  /
    //     4  7 13
    BinaryTree tree;
    for (int v : {8, 3, 10, 1, 6, 14, 4, 7, 13}) tree.insert(v);

    std::vector<int> expected = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    EXPECT_EQ(tree.preorder(), expected);
}

// ---------------------------------------------------------------------------
// Postorder – exact output verification (previously only size-checked)
// ---------------------------------------------------------------------------

TEST(BinaryTreeTest, PostorderExactValues) {
    BinaryTree tree;
    for (int v : {8, 3, 10, 1, 6, 14, 4, 7, 13}) tree.insert(v);

    std::vector<int> expected = {1, 4, 7, 6, 3, 13, 14, 10, 8};
    EXPECT_EQ(tree.postorder(), expected);
}

// ---------------------------------------------------------------------------
// Level-order – exact output verification (previously only size-checked)
// ---------------------------------------------------------------------------

TEST(BinaryTreeTest, LevelOrderExactValues) {
    BinaryTree tree;
    for (int v : {8, 3, 10, 1, 6, 14, 4, 7, 13}) tree.insert(v);

    std::vector<int> expected = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    EXPECT_EQ(tree.levelOrder(), expected);
}

// ---------------------------------------------------------------------------
// Inorder (for completeness – was already verified in main())
// ---------------------------------------------------------------------------

TEST(BinaryTreeTest, InorderExactValues) {
    BinaryTree tree;
    for (int v : {8, 3, 10, 1, 6, 14, 4, 7, 13}) tree.insert(v);

    std::vector<int> expected = {1, 3, 4, 6, 7, 8, 10, 13, 14};
    EXPECT_EQ(tree.inorder(), expected);
}

// ---------------------------------------------------------------------------
// Duplicate handling (count field)
// ---------------------------------------------------------------------------

TEST(BinaryTreeTest, DuplicatesAppearMultipleTimes) {
    BinaryTree tree;
    tree.insert(5);
    tree.insert(5);
    tree.insert(5);

    EXPECT_EQ(tree.inorder(), (std::vector<int>{5, 5, 5}));
    EXPECT_EQ(tree.preorder(), (std::vector<int>{5, 5, 5}));
    EXPECT_EQ(tree.postorder(), (std::vector<int>{5, 5, 5}));
    EXPECT_EQ(tree.levelOrder(), (std::vector<int>{5, 5, 5}));
}

TEST(BinaryTreeTest, DuplicatesInMixedTree) {
    BinaryTree tree;
    for (int v : {8, 3, 10, 6, 3, 6}) tree.insert(v);

    // inorder should be sorted with duplicates
    EXPECT_EQ(tree.inorder(), (std::vector<int>{3, 3, 6, 6, 8, 10}));

    // preorder: root first, then duplicates inline
    EXPECT_EQ(tree.preorder(), (std::vector<int>{8, 3, 3, 6, 6, 10}));

    // postorder: leaves first
    EXPECT_EQ(tree.postorder(), (std::vector<int>{6, 6, 3, 3, 10, 8}));

    // level-order: BFS
    EXPECT_EQ(tree.levelOrder(), (std::vector<int>{8, 3, 3, 10, 6, 6}));
}

// ---------------------------------------------------------------------------
// Right-skewed tree (ascending insertion)
// ---------------------------------------------------------------------------

TEST(BinaryTreeTest, RightSkewedTree) {
    BinaryTree tree;
    for (int v : {1, 2, 3, 4, 5}) tree.insert(v);

    EXPECT_EQ(tree.inorder(), (std::vector<int>{1, 2, 3, 4, 5}));
    EXPECT_EQ(tree.preorder(), (std::vector<int>{1, 2, 3, 4, 5}));
    EXPECT_EQ(tree.postorder(), (std::vector<int>{5, 4, 3, 2, 1}));
    EXPECT_EQ(tree.levelOrder(), (std::vector<int>{1, 2, 3, 4, 5}));
}

// ---------------------------------------------------------------------------
// Left-skewed tree (descending insertion)
// ---------------------------------------------------------------------------

TEST(BinaryTreeTest, LeftSkewedTree) {
    BinaryTree tree;
    for (int v : {5, 4, 3, 2, 1}) tree.insert(v);

    EXPECT_EQ(tree.inorder(), (std::vector<int>{1, 2, 3, 4, 5}));
    EXPECT_EQ(tree.preorder(), (std::vector<int>{5, 4, 3, 2, 1}));
    EXPECT_EQ(tree.postorder(), (std::vector<int>{1, 2, 3, 4, 5}));
    EXPECT_EQ(tree.levelOrder(), (std::vector<int>{5, 4, 3, 2, 1}));
}

// ---------------------------------------------------------------------------
// Contains – thorough edge cases
// ---------------------------------------------------------------------------

TEST(BinaryTreeTest, ContainsRoot) {
    BinaryTree tree;
    tree.insert(10);
    EXPECT_TRUE(tree.contains(10));
}

TEST(BinaryTreeTest, ContainsLeftChild) {
    BinaryTree tree;
    tree.insert(10);
    tree.insert(5);
    EXPECT_TRUE(tree.contains(5));
}

TEST(BinaryTreeTest, ContainsRightChild) {
    BinaryTree tree;
    tree.insert(10);
    tree.insert(15);
    EXPECT_TRUE(tree.contains(15));
}

TEST(BinaryTreeTest, ContainsDeepNode) {
    BinaryTree tree;
    for (int v : {10, 5, 15, 3, 7, 12, 20, 1}) tree.insert(v);
    EXPECT_TRUE(tree.contains(1));
    EXPECT_TRUE(tree.contains(20));
}

TEST(BinaryTreeTest, DoesNotContainMissingValues) {
    BinaryTree tree;
    for (int v : {10, 5, 15}) tree.insert(v);
    EXPECT_FALSE(tree.contains(0));
    EXPECT_FALSE(tree.contains(7));
    EXPECT_FALSE(tree.contains(12));
    EXPECT_FALSE(tree.contains(100));
}

// ---------------------------------------------------------------------------
// Negative values
// ---------------------------------------------------------------------------

TEST(BinaryTreeTest, NegativeValues) {
    BinaryTree tree;
    for (int v : {0, -5, 5, -10, -3, 3, 10}) tree.insert(v);

    EXPECT_EQ(tree.inorder(), (std::vector<int>{-10, -5, -3, 0, 3, 5, 10}));
    EXPECT_TRUE(tree.contains(-10));
    EXPECT_TRUE(tree.contains(-5));
    EXPECT_TRUE(tree.contains(-3));
    EXPECT_FALSE(tree.contains(-1));
}

// ---------------------------------------------------------------------------
// Large insertion – ensures no crash and correct ordering
// ---------------------------------------------------------------------------

TEST(BinaryTreeTest, LargeInsertionStaysSorted) {
    BinaryTree tree;
    // Insert in a pattern that exercises both subtrees
    for (int v : {50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56, 68, 81, 93})
        tree.insert(v);

    auto in = tree.inorder();
    // inorder must be sorted
    for (size_t i = 1; i < in.size(); ++i) {
        EXPECT_LE(in[i - 1], in[i]);
    }
    EXPECT_EQ(in.size(), 15u);
}

// ---------------------------------------------------------------------------
// Insert after querying – tree still works after reads
// ---------------------------------------------------------------------------

TEST(BinaryTreeTest, InsertAfterQuery) {
    BinaryTree tree;
    tree.insert(10);
    EXPECT_FALSE(tree.contains(20));

    tree.insert(20);
    EXPECT_TRUE(tree.contains(20));
    EXPECT_EQ(tree.inorder(), (std::vector<int>{10, 20}));
}

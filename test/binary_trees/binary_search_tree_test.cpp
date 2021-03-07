#include <gtest/gtest.h>

#include "nnoops/binary_trees/binary_search_tree.hpp"

using namespace nnoops;

TEST(BinarySearchTree, find_test) {
  BinarySearchTree<int> tree{[](const int& val1, const int& val2) -> int {
    if (val1 < val2) {
      return 1;
    }
    if (val1 > val2) {
      return -1;
    }
    return 0;
  }};

  EXPECT_EQ(tree.find(10), nullptr);

  tree.insert(10);
  tree.insert(13);
  tree.insert(12);
  tree.insert(10);
  tree.insert(111);

  const BinarySearchTreeNode<int>* el;

  el = tree.find(10);
  EXPECT_NE(el, nullptr);
  EXPECT_EQ(el->key_, 10);

  el = tree.find(13);
  EXPECT_NE(el, nullptr);
  EXPECT_EQ(el->key_, 13);

  el = tree.find(12);
  EXPECT_NE(el, nullptr);
  EXPECT_EQ(el->key_, 12);

  el = tree.find(111);
  EXPECT_NE(el, nullptr);
  EXPECT_EQ(el->key_, 111);

  el = tree.find(15);
  EXPECT_EQ(el, nullptr);

  el = tree.find(16);
  EXPECT_EQ(el, nullptr);

  el = tree.find(654);
  EXPECT_EQ(el, nullptr);

  el = tree.find(5432);
  EXPECT_EQ(el, nullptr);
}

TEST(BinarySearchTree, erase_test) {}

TEST(BinarySearchTree, next_prev_test) {
  BinarySearchTree<int> tree{[](const int& val1, const int& val2) -> int {
    if (val1 < val2) {
      return 1;
    }
    if (val1 > val2) {
      return -1;
    }
    return 0;
  }};

  tree.insert(1);
  tree.insert(3);
  tree.insert(4);
  tree.insert(8);
  tree.insert(6);
  tree.insert(7);
  tree.insert(10);
  tree.insert(14);
  tree.insert(13);
  tree.insert(5);
  tree.insert(2);

  const auto* node = tree.find(1);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 1);
  ASSERT_TRUE(node->parent_ == nullptr);

  node = tree.next(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 2);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.next(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 3);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.next(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 4);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.next(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 5);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.next(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 6);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.next(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 7);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.next(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 8);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.next(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 10);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.next(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 13);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.next(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 14);
  ASSERT_TRUE(node->parent_ != nullptr);

  auto* last = node;

  node = tree.next(node);
  ASSERT_TRUE(node == nullptr);

  node = last;
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 14);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.prev(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 13);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.prev(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 10);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.prev(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 8);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.prev(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 7);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.prev(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 6);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.prev(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 5);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.prev(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 4);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.prev(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 3);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.prev(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 2);
  ASSERT_TRUE(node->parent_ != nullptr);

  node = tree.prev(node);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key_, 1);
  ASSERT_TRUE(node->parent_ == nullptr);
}
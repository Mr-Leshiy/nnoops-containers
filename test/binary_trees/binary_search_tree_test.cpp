#include <gtest/gtest.h>

#include "nnoops/binary_trees/binary_search_tree.hpp"

using namespace nnoops;

auto cmp = [](const int& val1, const int& val2) -> int {
  if (val1 < val2) {
    return 1;
  }
  if (val1 > val2) {
    return -1;
  }
  return 0;
};

TEST(BinarySearchTree, find_test) {
  BinarySearchTree<int> tree{cmp};

  EXPECT_EQ(tree.find(10), nullptr);

  tree.insert(10);
  tree.insert(13);
  tree.insert(12);
  tree.insert(10);
  tree.insert(111);

  ASSERT_EQ(tree.size(), 4);

  const BinarySearchTreeNode<int>* el;

  el = tree.find(10);
  ASSERT_NE(el, nullptr);
  ASSERT_EQ(el->getKey(), 10);

  el = tree.find(13);
  ASSERT_NE(el, nullptr);
  ASSERT_EQ(el->getKey(), 13);

  el = tree.find(12);
  ASSERT_NE(el, nullptr);
  ASSERT_EQ(el->getKey(), 12);

  el = tree.find(111);
  ASSERT_NE(el, nullptr);
  ASSERT_EQ(el->getKey(), 111);

  el = tree.find(15);
  ASSERT_EQ(el, nullptr);

  el = tree.find(16);
  ASSERT_EQ(el, nullptr);

  el = tree.find(654);
  ASSERT_EQ(el, nullptr);

  el = tree.find(5432);
  ASSERT_EQ(el, nullptr);
}

TEST(BinarySearchTree, erase_test) {
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

  ASSERT_EQ(tree.size(), 11);

  ASSERT_TRUE(tree.find(3) != nullptr);
  tree.erase(3);
  ASSERT_EQ(tree.size(), 10);
  ASSERT_TRUE(tree.find(3) == nullptr);

  ASSERT_TRUE(tree.find(3) == nullptr);
  tree.erase(3);
  ASSERT_EQ(tree.size(), 10);
  ASSERT_TRUE(tree.find(3) == nullptr);

  ASSERT_TRUE(tree.find(4) != nullptr);
  tree.erase(4);
  ASSERT_EQ(tree.size(), 9);
  ASSERT_TRUE(tree.find(4) == nullptr);

  ASSERT_TRUE(tree.find(1) != nullptr);
  tree.erase(1);
  ASSERT_EQ(tree.size(), 8);
  ASSERT_TRUE(tree.find(1) == nullptr);

  ASSERT_TRUE(tree.find(5) != nullptr);
  tree.erase(5);
  ASSERT_EQ(tree.size(), 7);
  ASSERT_TRUE(tree.find(5) == nullptr);

  ASSERT_TRUE(tree.find(5) == nullptr);
  tree.erase(5);
  ASSERT_EQ(tree.size(), 7);
  ASSERT_TRUE(tree.find(5) == nullptr);

  ASSERT_TRUE(tree.find(10) != nullptr);
  tree.erase(10);
  ASSERT_EQ(tree.size(), 6);
  ASSERT_TRUE(tree.find(10) == nullptr);

  ASSERT_TRUE(tree.find(7) != nullptr);
  tree.erase(7);
  ASSERT_EQ(tree.size(), 5);
  ASSERT_TRUE(tree.find(7) == nullptr);

  ASSERT_TRUE(tree.find(6) != nullptr);
  tree.erase(6);
  ASSERT_EQ(tree.size(), 4);
  ASSERT_TRUE(tree.find(6) == nullptr);

  ASSERT_TRUE(tree.find(14) != nullptr);
  tree.erase(14);
  ASSERT_EQ(tree.size(), 3);
  ASSERT_TRUE(tree.find(14) == nullptr);

  ASSERT_TRUE(tree.find(13) != nullptr);
  tree.erase(13);
  ASSERT_EQ(tree.size(), 2);
  ASSERT_TRUE(tree.find(13) == nullptr);

  ASSERT_TRUE(tree.find(2) != nullptr);
  tree.erase(2);
  ASSERT_EQ(tree.size(), 1);
  ASSERT_TRUE(tree.find(2) == nullptr);

  ASSERT_TRUE(tree.find(2) == nullptr);
  tree.erase(2);
  ASSERT_EQ(tree.size(), 1);
  ASSERT_TRUE(tree.find(2) == nullptr);

  ASSERT_TRUE(tree.find(8) != nullptr);
  tree.erase(8);
  ASSERT_EQ(tree.size(), 0);
  ASSERT_TRUE(tree.find(8) == nullptr);
}

TEST(BinarySearchTree, next_prev_test) {
  BinarySearchTree<int> tree{cmp};

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

  ASSERT_EQ(tree.size(), 11);

  auto* node = tree.find(1);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 1);
  ASSERT_TRUE(node->getParent() == nullptr);

  node = node->next();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 2);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->next();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 3);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->next();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 4);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->next();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 5);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->next();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 6);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->next();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 7);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->next();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 8);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->next();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 10);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->next();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 13);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->next();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 14);
  ASSERT_TRUE(node->getParent() != nullptr);

  auto* last = node;

  node = node->next();
  ASSERT_TRUE(node == nullptr);

  node = last;
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 14);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->prev();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 13);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->prev();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 10);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->prev();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 8);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->prev();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 7);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->prev();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 6);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->prev();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 5);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->prev();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 4);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->prev();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 3);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->prev();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 2);
  ASSERT_TRUE(node->getParent() != nullptr);

  node = node->prev();
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->getKey(), 1);
  ASSERT_TRUE(node->getParent() == nullptr);
}
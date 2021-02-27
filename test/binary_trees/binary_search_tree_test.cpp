#include <gtest/gtest.h>

#include "nnoops/binary_trees/binary_search_tree.hpp"

using namespace nnoops;

TEST(BinarySearchTree, basic_test) {
  BinarySearchTree<int> tree{
      [](const int& val1, const int& val2) -> bool { return val1 < val2; }};

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
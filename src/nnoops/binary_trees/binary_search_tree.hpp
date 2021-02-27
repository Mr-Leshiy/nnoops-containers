#ifndef NNOOPS_BINARY_TREES_BINARY_SEARCH_TREE_HPP_
#define NNOOPS_BINARY_TREES_BINARY_SEARCH_TREE_HPP_

namespace nnoops {

template <typename T>
struct BinarySearchTreeNode {
  T key_;
  BinarySearchTreeNode* left_;
  BinarySearchTreeNode* right_;
  BinarySearchTreeNode* parent_;
};

template <typename T>
struct BinarySearchTree {
  ~BinarySearchTree() = default;

 private:
  BinarySearchTreeNode<T> root{{}, nullptr, nullptr, nullptr};
};

}  // namespace nnoops

#endif
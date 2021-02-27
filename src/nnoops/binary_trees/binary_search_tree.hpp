#ifndef NNOOPS_BINARY_TREES_BINARY_SEARCH_TREE_HPP_
#define NNOOPS_BINARY_TREES_BINARY_SEARCH_TREE_HPP_

#include <functional>

namespace nnoops {

template <typename T>
struct BinarySearchTreeNode {
  T key_{};
  BinarySearchTreeNode* left_{nullptr};
  BinarySearchTreeNode* right_{nullptr};
  BinarySearchTreeNode* parent_{nullptr};
};

template <typename T>
BinarySearchTreeNode<T>* minimum(BinarySearchTreeNode<T>* node) {
  auto* walk_node = node;
  if (walk_node == nullptr) {
    return nullptr;
  }

  while (walk_node->left_ != nullptr) {
    walk_node = walk_node->left_;
  }
  return walk_node;
}

template <typename T>
BinarySearchTreeNode<T>* maximum(BinarySearchTreeNode<T>* node) {
  auto* walk_node = node;
  if (walk_node == nullptr) {
    return nullptr;
  }

  while (walk_node->right_ != nullptr) {
    walk_node = walk_node->right_;
  }
  return walk_node;
}

template <typename T>
struct BinarySearchTree {
  using node_t = BinarySearchTreeNode<T>;

  ~BinarySearchTree() = default;

  BinarySearchTree(std::function<bool(const int& val1, const int& val2)> cmp)
      : cmp_(cmp) {}

  const node_t* find(const T& key) const {
    auto* walk_node = root_;
    while (walk_node != nullptr) {
      if (walk_node->key_ == key) {
        return walk_node;
      }
      if (cmp_(key, walk_node->key_)) {
        walk_node = walk_node->left_;
      } else {
        walk_node = walk_node->right_;
      }
    }
    return nullptr;
  }

  const node_t* insert(const T& key) {
    ++size_;

    if (root_ == nullptr) {
      root_ = new node_t{key, nullptr, nullptr, nullptr};
      return root_;
    }

    auto* walk_node = root_;
    auto* new_node = new node_t{key, nullptr, nullptr, nullptr};

    while (walk_node != nullptr) {
      if (cmp_(walk_node->key_, key)) {
        if (walk_node->right_ != nullptr) {
          walk_node = walk_node->right_;
        } else {
          new_node->parent_ = walk_node;
          walk_node->right_ = new_node;
          break;
        }
      } else {
        if (walk_node->left_ != nullptr) {
          walk_node = walk_node->left_;
        } else {
          new_node->parent_ = walk_node;
          walk_node->left_ = new_node;
          break;
        }
      }
    }

    return new_node;
  }

 private:
  BinarySearchTreeNode<T>* root_{nullptr};
  std::function<bool(const T& val1, const T& val2)> cmp_{};
  size_t size_;
};

}  // namespace nnoops

#endif
#ifndef NNOOPS_BINARY_TREES_BINARY_SEARCH_TREE_HPP_
#define NNOOPS_BINARY_TREES_BINARY_SEARCH_TREE_HPP_

#include <functional>

#include "nnoops/binary_trees/base_tree.hpp"

namespace nnoops {

template <typename T>
struct BinarySearchTreeNode {
  using key_t = T;

  T key_{};
  BinarySearchTreeNode* left_{nullptr};
  BinarySearchTreeNode* right_{nullptr};
  BinarySearchTreeNode* parent_{nullptr};
};

template <typename T>
struct BinarySearchTree : public BaseTree<BinarySearchTreeNode<T>> {
  using node_t = BinarySearchTreeNode<T>;

  ~BinarySearchTree() override { clear(); };

  BinarySearchTree(std::function<bool(const int& val1, const int& val2)> cmp)
      : cmp_(cmp) {}

  const node_t* next(const node_t* node) override { return _next(node); }

  const node_t* prev(const node_t* node) override { return _prev(node); }

  const node_t* find(const T& key) const override {
    node_t* walk_node = root_;
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

  const node_t* insert(const T& key) override {
    node_t* new_node = new node_t{key, nullptr, nullptr, nullptr};

    if (root_ == nullptr) {
      root_ = new_node;
      return root_;
    }

    node_t* walk_node = root_;

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

  const node_t* erase(const node_t* node) override {
    node_t* next = _next(node);
    node_t* parent = node->parent_;

    // first case
    if (node->left_ == nullptr && node->right_ == nullptr) {
      if (node == root_) {
        delete node;
        return next;
      }
      if (parent->left_ == node) {
        parent->left_ = nullptr;
      }
      if (parent->right_ == node) {
        parent->right_ = nullptr;
      }
      delete node;
      return next;
    }

    // second case
    if (node->left_ == nullptr) {
      if (node == root_) {
        root_ = node->right_;
        delete node;
        return next;
      }
      if (parent->left_ == node) {
        parent->left_ = node->right_;
        delete node;
        return next;
      }
      if (parent->right_ == node) {
        parent->right_ = node->right_;
        delete node;
        return next;
      }
    }
    //
    if (node->right_ == nullptr) {
      if (node == root_) {
        root_ = node->left_;
        delete node;
        return next;
      }
      if (parent->left_ == node) {
        parent->left_ = node->left_;
        delete node;
        return next;
      }
      if (parent->right_ == node) {
        parent->right_ = node->left_;
        delete node;
        return next;
      }
    }

    // third case

    next->left_ = node->left_;
    if (node == root_) {
      root_ = next;
      delete node;
      return next;
    }
    if (parent->left_ == node) {
      parent->left_ = next;
    }
    if (parent->right_ == node) {
      parent->left_ = next;
    }

    delete node;
    return next;
  }

  void clear() override {
    const auto* walk_node = minimum(root_);
    while (walk_node != nullptr) {
      walk_node = erase(walk_node);
    }
  }

 private:
  node_t* minimum(node_t* node) {
    auto* walk_node = node;
    if (walk_node == nullptr) {
      return nullptr;
    }

    while (walk_node->left_ != nullptr) {
      walk_node = walk_node->left_;
    }
    return walk_node;
  }

  node_t* maximum(node_t* node) {
    auto* walk_node = node;
    if (walk_node == nullptr) {
      return nullptr;
    }

    while (walk_node->right_ != nullptr) {
      walk_node = walk_node->right_;
    }
    return walk_node;
  }

  node_t* _next(const node_t* node) {
    if (node->right_ != nullptr) {
      return minimum(node->right_);
    }

    auto* walk_node1 = node->parent_;
    auto* walk_node2 = node;
    while (walk_node1 != nullptr && walk_node1->right_ == walk_node2) {
      walk_node2 = walk_node1;
      walk_node1 = walk_node1->parent_;
    }
    return walk_node1;
  }

  node_t* _prev(const node_t* node) {
    if (node->left_ != nullptr) {
      return maximum(node->left_);
    }

    auto* walk_node1 = node->parent_;
    auto* walk_node2 = node;
    while (walk_node1 != nullptr && walk_node1->left_ == walk_node2) {
      walk_node2 = walk_node1;
      walk_node1 = walk_node1->parent_;
    }
    return walk_node1;
  }

  node_t* root_{nullptr};
  std::function<bool(const T& val1, const T& val2)> cmp_{};
};

}  // namespace nnoops

#endif
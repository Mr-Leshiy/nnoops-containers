#ifndef NNOOPS_BINARY_TREES_BINARY_SEARCH_TREE_HPP_
#define NNOOPS_BINARY_TREES_BINARY_SEARCH_TREE_HPP_

#include <assert.h>

#include <functional>

#include "nnoops/binary_trees/base_tree.hpp"

namespace nnoops {

template <typename T>
struct BinarySearchTreeNode {
  using key_t = T;
  using node_t = BinarySearchTreeNode<T>;

  key_t getKey() const { return key_; }

  const node_t* getLeft() const { return left_; }

  const node_t* getRight() const { return right_; }

  const node_t* getParent() const { return parent_; }

  node_t* minimum() {
    auto* walk_node = this;
    if (walk_node == nullptr) {
      return nullptr;
    }

    while (walk_node->left_ != nullptr) {
      walk_node = walk_node->left_;
    }
    return walk_node;
  }

  node_t* maximum() {
    auto* walk_node = this;
    if (walk_node == nullptr) {
      return nullptr;
    }

    while (walk_node->right_ != nullptr) {
      walk_node = walk_node->right_;
    }
    return walk_node;
  }

  node_t* next() {
    if (this->right_ != nullptr) {
      return this->right_->minimum();
    }

    auto* walk_node1 = this->parent_;
    auto* walk_node2 = this;
    while (walk_node1 != nullptr && walk_node1->right_ == walk_node2) {
      walk_node2 = walk_node1;
      walk_node1 = walk_node1->parent_;
    }
    return walk_node1;
  }

  node_t* prev() {
    if (this->left_ != nullptr) {
      return this->left_->maximum();
    }

    auto* walk_node1 = this->parent_;
    auto* walk_node2 = this;
    while (walk_node1 != nullptr && walk_node1->left_ == walk_node2) {
      walk_node2 = walk_node1;
      walk_node1 = walk_node1->parent_;
    }
    return walk_node1;
  }

  template <typename K>
  friend class BinarySearchTree;

 private:
  BinarySearchTreeNode(const key_t& key,
                       node_t* left,
                       node_t* right,
                       node_t* parent)
      : key_(key), left_(left), right_(right), parent_(parent) {}

  key_t key_{};
  BinarySearchTreeNode* left_{nullptr};
  BinarySearchTreeNode* right_{nullptr};
  BinarySearchTreeNode* parent_{nullptr};
};

template <typename T>
struct BinarySearchTree : public BaseTree<BinarySearchTreeNode<T>> {
  using node_t = BinarySearchTreeNode<T>;
  using key_t = T;
  using cmp_t = std::function<int(const int& val1, const int& val2)>;

  ~BinarySearchTree() override { clear(); };

  BinarySearchTree(cmp_t cmp) : cmp_(cmp) {}

  node_t* find(const key_t& key) override {
    node_t* walk_node = root_;
    while (walk_node != nullptr) {
      int res = cmp_(key, walk_node->key_);
      if (res == 0) {
        return walk_node;
      }
      if (res > 0) {
        walk_node = walk_node->left_;
      }
      if (res < 0) {
        walk_node = walk_node->right_;
      }
    }
    return nullptr;
  }

  node_t* insert(const key_t& key) override {
    if (root_ == nullptr) {
      ++size_;
      root_ = new node_t{key, nullptr, nullptr, nullptr};
      return root_;
    }

    node_t* walk_node = root_;
    while (walk_node != nullptr) {
      int res = cmp_(key, walk_node->key_);
      if (res == 0) {
        return walk_node;
      }
      if (res > 0) {
        if (walk_node->left_ != nullptr) {
          walk_node = walk_node->left_;
        } else {
          ++size_;
          walk_node->left_ = new node_t{key, nullptr, nullptr, walk_node};
          return walk_node->left_;
        }
      }
      if (res < 0) {
        if (walk_node->right_ != nullptr) {
          walk_node = walk_node->right_;
        } else {
          ++size_;
          walk_node->right_ = new node_t{key, nullptr, nullptr, walk_node};
          return walk_node->right_;
        }
      }
    }

    assert(false);
    return nullptr;
  }

  node_t* erase(const key_t& key) override { return erase(find(key)); }

  node_t* erase(node_t* node) override {
    if (node == nullptr) {
      return nullptr;
    }

    node_t* next = node->next();
    node_t* parent = node->parent_;

    // first case
    if (node->left_ == nullptr && node->right_ == nullptr) {
      if (node == root_) {
        root_ = nullptr;

        --size_;
        delete node;
        return next;
      }
      if (parent->left_ == node) {
        parent->left_ = nullptr;
      }
      if (parent->right_ == node) {
        parent->right_ = nullptr;
      }

      --size_;
      delete node;
      return next;
    }

    // second case
    if (node->left_ == nullptr) {
      if (node == root_) {
        root_ = node->right_;
        root_->parent_ = nullptr;

        --size_;
        delete node;
        return next;
      }
      if (parent->left_ == node) {
        parent->left_ = node->right_;
        parent->left_->parent_ = parent;

        --size_;
        delete node;
        return next;
      }
      if (parent->right_ == node) {
        parent->right_ = node->right_;
        parent->right_->parent_ = parent;

        --size_;
        delete node;
        return next;
      }
    }
    //
    if (node->right_ == nullptr) {
      if (node == root_) {
        root_ = node->left_;
        root_->parent_ = nullptr;

        --size_;
        delete node;
        return next;
      }
      if (parent->left_ == node) {
        parent->left_ = node->left_;
        parent->left_->parent_ = parent;

        --size_;
        delete node;
        return next;
      }
      if (parent->right_ == node) {
        parent->right_ = node->left_;
        parent->right_->parent_ = parent;

        --size_;
        delete node;
        return next;
      }
    }

    // third case

    if (next->parent_->left_ == next) {
      next->parent_->left_ = next->right_;
      if (next->right_ != nullptr) {
        next->right_->parent_ = next->parent_;
      }
    }
    if (next->parent_->right_ == next) {
      next->parent_->right_ = next->right_;
      if (next->right_ != nullptr) {
        next->right_->parent_ = next->parent_;
      }
    }

    node->key_ = next->key_;

    --size_;
    delete next;
    return node;
  }

  void clear() override {
    auto* walk_node = root_->minimum();
    while (walk_node != nullptr) {
      walk_node = erase(walk_node);
    }
    assert(size_ == 0);
  }

  size_t size() const override {
    assert(size_ >= 0);
    return size_;
  }

 private:
  node_t* root_{nullptr};
  // 0 = equals, positive = val1 < val2, negative = val1 > val2
  cmp_t cmp_{};
  size_t size_{0};
};

}  // namespace nnoops

#endif
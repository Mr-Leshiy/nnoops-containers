#ifndef NNOOPS_BASE_TREE_HPP_
#define NNOOPS_BASE_TREE_HPP_

namespace nnoops {

template <typename node_t>
struct BaseTree {
  using key_t = typename node_t::key_t;

  virtual ~BaseTree() = default;

  virtual const node_t* prev(const node_t* node) = 0;
  virtual const node_t* next(const node_t* node) = 0;
  virtual const node_t* find(const key_t& key) const = 0;
  virtual const node_t* insert(const key_t& key) = 0;
  virtual const node_t* erase(const node_t* node) = 0;
  virtual void clear() = 0;
  virtual size_t size() const = 0;
};

}  // namespace nnoops

#endif
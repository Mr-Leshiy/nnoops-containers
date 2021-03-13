#ifndef NNOOPS_CONTAINERS_MAP_HPP_
#define NNOOPS_CONTAINERS_MAP_HPP_

#include <type_traits>

#include "nnoops/binary_trees/base_tree.hpp"
namespace nnoops {

template <typename T, template <typename T1> typename tree>
struct Map {
  using tree_t = tree<T>;
  using node_t = typename tree_t::node_t;
  using key_t = typename tree_t::key_t;
  using cmp_t = typename tree_t::cmp_t;

  Map(cmp_t cmp) : tree_(cmp) {}

  size_t size() const { return tree_.size(); }
  bool empty() const { return tree_.size() == 0; }

 private:
  using enable_t = typename std::enable_if<
      std::is_base_of<BaseTree<node_t>, tree_t>::value>::type;

  tree_t tree_;
};

}  // namespace nnoops

#endif
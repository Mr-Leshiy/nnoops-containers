#ifndef NNOOPS_CONTAINERS_MAP_HPP_
#define NNOOPS_CONTAINERS_MAP_HPP_

#include <type_traits>

#include "nnoops/binary_trees/base_tree.hpp"
namespace nnoops {

template <typename tree_t>
struct Map {
  using node_t = typename tree_t::node_t;

  using tmp_t = typename std::enable_if<
      std::is_base_of<BaseTree<node_t>, tree_t>::value>::type;
};

}  // namespace nnoops

#endif
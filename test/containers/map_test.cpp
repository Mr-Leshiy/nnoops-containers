#include <gtest/gtest.h>

#include "nnoops/binary_trees/binary_search_tree.hpp"
#include "nnoops/containers/map.hpp"

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

TEST(Map, base_test) { Map<int, BinarySearchTree> map{cmp}; }
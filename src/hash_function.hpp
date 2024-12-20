#include <functional>
#include <string_view>

#include "absl/hash/hash.h"

template <typename T>
struct StandardHashType {
  using HashType = std::hash<T>;
  static constexpr std::string_view kName = "std::hash";
};

template <typename T>
struct AbseilHashType {
  using HashType = absl::Hash<T>;
  static constexpr std::string_view kName = "absl::Hash";
};

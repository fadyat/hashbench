#pragma once

#include <functional>

#include "absl/container/flat_hash_map.h"
#include "sparsehash/dense_hash_map"

template <typename Key, typename Value, typename Hash = std::hash<Key>>
struct UnorderedMapType {
  using HashTable = std::unordered_map<Key, Value, Hash>;
  static constexpr const std::string_view kName = "std::unordered_map";
};

template <typename Key, typename Value, typename Hash = std::hash<Key>>
struct AbseilHashTableType {
  using HashTable = absl::flat_hash_map<Key, Value, Hash>;
  static constexpr const std::string_view kName = "absl::flat_hash_map";
};

template <typename Key, typename Value, typename Hash = std::hash<Key>>
struct GoogleDenseHashTableType {
  using HashTable = google::dense_hash_map<Key, Value, Hash>;
  static constexpr const std::string_view kName = "google::dense_hash_map";
};

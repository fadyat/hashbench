#include <sys/types.h>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "hash_table.hpp"
#include "utils.hpp"

namespace {

struct AggregationStats {
  size_t map_size;
  size_t map_capacity;
  size_t memory_usage;
  std::chrono::nanoseconds duration;

  void show_stats(std::string_view name) const {
    std::cout << name << ":\n";
    std::cout << "  Map size: " << map_size << "\n";
    std::cout << "  Map capacity: " << map_capacity << "\n";
    std::cout << "  Memory usage: " << memory_usage << " bytes" << "\n";
    std::cout << "  Duration: " << duration.count() << " ns" << "\n";
  }
};

template <typename Key, typename HashTable, typename InitFn = std::function<void(HashTable &)>>
std::unique_ptr<AggregationStats> aggregation_test(std::vector<Key> &keys, InitFn init) {
  using clock = std::chrono::steady_clock;

  auto start = clock::now();
  size_t initial_memory_usage = get_memory_usage();
  AggregationStats stats;

  // Here we making some aggregation work, for example, here we counting
  // the number of occurrences of each key.
  //
  // The SQL equivalent of this code is:
  //  SELECT key, COUNT(*) FROM rows GROUP BY key;
  {
    HashTable hash_table;
    init(hash_table);

    for (const auto &key : keys) {
      ++hash_table[key];
    }

    stats.duration = std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - start);
    stats.memory_usage = std::max(get_memory_usage() - initial_memory_usage, get_page_size());
    stats.map_size = hash_table.size();
    stats.map_capacity = hash_table.bucket_count();
  }

  return std::make_unique<AggregationStats>(stats);
}

};

int main(int argc, char *argv[]) {
  std::string hashmap_type = argc > 1 ? argv[1] : "std::unordered_map";
  std::vector<uint64_t> watch_ids = read_tsv_column<uint64_t>("../datasets/hits_v1.tsv", 0);

  std::unique_ptr<AggregationStats> stats;
  if (hashmap_type == "std::unordered_map") {
    using HashTable = UnorderedMapType<uint64_t, size_t>::HashTable;
    stats = aggregation_test<uint64_t, HashTable>(watch_ids, [](HashTable &hash_table) {});
  } else if (hashmap_type == "absl::flat_hash_map") {
    using HashTable = AbseilHashTableType<uint64_t, size_t>::HashTable;
    stats = aggregation_test<uint64_t, HashTable>(watch_ids, [](HashTable &hash_table) {});
  } else if (hashmap_type == "google::dense_hash_map") {
    using HashTable = GoogleDenseHashTableType<uint64_t, size_t>::HashTable;
    stats = aggregation_test<uint64_t, HashTable>(watch_ids, [](HashTable &hash_table) { hash_table.set_empty_key(0); });
  }

  if (stats) {
    stats->show_stats(hashmap_type);
  }
}

#include <cstddef>
#ifdef __linux__

#include <unistd.h>

#include <fstream>

#include "utils.hpp"

// https://man7.org/linux/man-pages/man3/sysconf.3.html
size_t get_page_size() {
  size_t page_size = sysconf(_SC_PAGESIZE);
  return page_size < 0 ? 0 : page_size;
}

// https://man7.org/linux/man-pages/man5/proc_pid_statm.5.html
size_t get_memory_usage() {
  std::ifstream file("/proc/self/statm");
  size_t ignore;
  size_t resident;
  file >> ignore >> resident;
  return resident * get_page_size();
}

#else

size_t get_page_size() { return 0; }
size_t get_memory_usage() { return 0; }

#endif

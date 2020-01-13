#ifndef RIO_MAIN
#define RIO_MAIN

#include <string>

namespace rio {

auto read(std::string filename) -> int;
auto write(std::string filename, int num_events) -> int;

} // namespace rio

#endif /* ifndef RIO_MAIN */

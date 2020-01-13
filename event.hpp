#ifndef RIO_EVENT
#define RIO_EVENT

#include <Rtypes.h>
#include <TObject.h>
#include <array>
#include <cstddef>
#include <random>

namespace rio {

// Adjust size of event
struct event : TObject {
  using element_type = int;
  static constexpr std::size_t size_in_bytes = 1024;
  static constexpr std::size_t num_elements =
      size_in_bytes / sizeof(element_type);
  std::array<int, num_elements> d;

  event() {
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int> uniform_dist;
    for (std::size_t i(0); i < num_elements; ++i) {
      d[i] = uniform_dist(e);
    }
  }

  ClassDef(event, 1);
};

} // namespace rio

#endif /* ifndef RIO_EVENT */

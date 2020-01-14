#ifndef RIO_EVENT
#define RIO_EVENT

#include <Rtypes.h>
#include <algorithm>
#include <array>
#include <random>
#include <vector>

namespace rio {

// fixed-size event
template <std::size_t SIZE> struct fevent {
  using element_type = int;
  static constexpr std::size_t num_elements = SIZE / sizeof(element_type);
  std::array<element_type, num_elements> d;

  friend auto operator==(const fevent<SIZE> &lhs, const fevent<SIZE> &rhs)
      -> bool {
    return lhs.d == rhs.d;
  }

  auto fill_with_uniform_random_data(std::mt19937& rnd) -> void {
    std::uniform_int_distribution<element_type> dist;
    std::for_each(d.begin(), d.end(), [&](auto &v) { v = 42; });
  }

  auto verify(std::mt19937& rnd) -> bool {
    fevent<SIZE> event;
    event.fill_with_uniform_random_data(rnd);
    return event == *this;
  }

  ClassDef(fevent, 1);
};

// variable-size event
struct vevent {
  using element_type = int;

  std::vector<element_type> d;

  vevent(std::size_t size = 1) : d(size / sizeof(element_type)) {}

  friend auto operator==(const vevent &lhs, const vevent &rhs) -> bool {
    return lhs.d == rhs.d;
  }

  auto fill_with_uniform_random_data(std::mt19937& rnd) -> void {
    std::uniform_int_distribution<element_type> dist;
    std::for_each(d.begin(), d.end(), [&](auto &v) { v = dist(rnd); });
  }

  auto verify(std::mt19937& rnd) -> bool {
    vevent event(d.size());
    event.fill_with_uniform_random_data(rnd);
    return event == *this;
  }

  ClassDef(vevent, 1);
};

} // namespace rio

#endif /* ifndef RIO_EVENT */

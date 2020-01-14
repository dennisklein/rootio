#ifndef RIO_WRITE
#define RIO_WRITE

#include "event.hpp"

#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <memory>
#include <random>

namespace rio {

template<typename E>
auto write(std::string filename, std::mt19937& rnd, int num_events) -> std::size_t {
  TFile file(filename.c_str(), "RECREATE", "test", 0); // no compression
  TTree tree("Events", "Test event container", 0);

  std::unique_ptr<E> event(new E());
  auto event_ptr(event.get());
  event->fill_with_uniform_random_data(rnd);
  tree.Branch("event", &event_ptr);
  tree.Fill();

  for (int i(1); i < num_events; ++i) {
    event.reset(new E());
    event_ptr = event.get();
    event->fill_with_uniform_random_data(rnd);
    tree.Fill();
  }

  tree.Write();
  file.Close();

  return file.GetSize();
}

} // namespace rio

#endif /* ifndef RIO_WRITE */

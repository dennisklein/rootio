#include "event.hpp"
#include "main.hpp"

#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <memory>
#include <vector>

namespace rio {

auto write(std::string filename, int num_events) -> int {
  TFile file(filename.c_str(), "RECREATE");
  TTree tree("Events", "Test event container");

  auto event(std::make_unique<event>());
  auto event_ptr(event.get());
  tree.Branch("event", &event_ptr);
  tree.Fill();

  for (int i(1); i < num_events; ++i) {
    event.reset();
    event_ptr = event.get();
    tree.Fill();
  }

  tree.Write();
  file.Close();

  return file.GetSize();
}

} // namespace rio

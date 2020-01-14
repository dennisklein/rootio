#ifndef RIO_READ
#define RIO_READ

#include "event.hpp"

#include <TFile.h>
#include <TTree.h>
#include <TTreeCache.h>
#include <iostream>
#include <memory>
#include <tuple>

namespace rio {

template <typename E>
auto read(std::string filename, std::mt19937 &rnd)
    -> std::tuple<std::size_t, std::size_t> {
  TFile file(filename.c_str(), "READ");
  TTree* tree(nullptr);
  file.GetObject("Events", tree);

  tree->SetCacheSize(16 * 1024 * 1024);
  tree->AddBranchToCache("*", true);

  auto event(std::make_unique<E>());
  auto event_ptr(event.get());
  tree->SetBranchAddress("event", &event_ptr);

  auto num_events = tree->GetEntries();
  for (int i(0); i < num_events; ++i) {
    tree->GetEvent(i);
    if (!event->verify(rnd)) {
      std::cerr << "event #" << i << " failed data verification" << std::endl;
    }
  }

  tree->PrintCacheStats();
  std::cout << std::endl;

  std::size_t bytes(file.GetCacheRead()->GetBytesRead());
  bytes += file.GetCacheRead()->GetNoCacheBytesRead();
  file.Close();

  return {bytes, num_events};
}

} // namespace rio

#endif /* ifndef RIO_READ */

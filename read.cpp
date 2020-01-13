#include "event.hpp"
#include "main.hpp"

#include <TFile.h>
#include <TTree.h>
#include <TTreeCache.h>
#include <iostream>
#include <memory>

namespace rio {

auto read(std::string filename) -> int {
  TFile file(filename.c_str(), "READ");
  TTree* tree(nullptr);
  file.GetObject("Events", tree);

  tree->SetCacheSize(16 * 1024 * 1024);
  tree->AddBranchToCache("*", true);

  auto event(std::make_unique<event>());
  auto num_events = tree->GetEntries();
  for (int i(0); i < num_events; ++i) {
    tree->GetEvent(i);
  }

  tree->PrintCacheStats();
  std::cout << std::endl;
  file.Close();

  return file.GetSize();
}

} // namespace rio

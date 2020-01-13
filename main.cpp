#include "main.hpp"

#include <TEnv.h>
#include <TStopwatch.h>
#include <TROOT.h>
#include <cstring>
#include <iostream>
#include <string>

namespace rio {

auto print_usage() {
  std::cout << "Usage: rio w [FILENAME] [NUM_EVENTS]" << std::endl
            << "       rio r [FILENAME]" << std::endl;
}

} // namespace rio

int main(int argc, char *argv[]) {
  // Parse command line args
  if (argc < 1 || argc > 4) {
    rio::print_usage();
    return EXIT_FAILURE;
  }
  bool write(std::strncmp(argv[1], "w", 1) == 0);
  bool read(std::strncmp(argv[1], "r", 1) == 0);
  if (!write && !read) {
    rio::print_usage();
    return EXIT_FAILURE;
  }
  std::string filename(argc >= 3 ? argv[2] : "events.root");
  int num_events(argc >= 4 ? std::atoi(argv[3]) : 100);

  // Configure ROOT
  ROOT::EnableImplicitMT(4);
  gEnv->SetValue("TFile.AsyncPrefetching", 1);

  // Run timed operation
  TStopwatch sw;
  sw.Start();

  int bytes(0);
  if (write) {
    bytes = rio::write(filename, num_events);
  } else {
    bytes = rio::read(filename);
  }

  sw.Stop();

  // Print statistics
  float MiB(bytes / (1024. * 1024.));
  auto elapsed_seconds(sw.RealTime());
  float rate_MiBps(MiB / elapsed_seconds);
  std::cout << MiB << " MiB (" << bytes << " bytes) in " << elapsed_seconds
            << " seconds (" << rate_MiBps << " MiB/s)." << std::endl;

  return EXIT_SUCCESS;
}

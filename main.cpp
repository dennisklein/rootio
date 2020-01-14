#include "event.hpp"
#include "read.hpp"
#include "write.hpp"

#include <TEnv.h>
#include <TStopwatch.h>
#include <TROOT.h>
#include <cstring>
#include <iostream>
#include <random>
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
  std::size_t num_events(argc >= 4 ? std::atoi(argv[3]) : 100);

  // Configure ROOT
  // ROOT::EnableImplicitMT(4);
  // gEnv->SetValue("TFile.AsyncPrefetching", 1);

  std::mt19937 rnd;
  rnd.seed(555);

  // Run timed operation
  TStopwatch sw;
  sw.Start();

  int bytes(0);
  constexpr std::size_t event_size(32);

  if (write) {
    bytes = rio::write<rio::fevent<event_size>>(filename, rnd, num_events);
  } else {
    std::tie(bytes, num_events) = rio::read<rio::fevent<event_size>>(filename, rnd);
  }

  sw.Stop();

  // Print statistics
  float MiB(bytes / (1024. * 1024.));
  auto elapsed_seconds(sw.RealTime());
  float rate_MiBps(MiB / elapsed_seconds);
  std::cout << (write ? "wrote " : "read ")
            << num_events << " events (" << event_size << " bytes)" << std::endl
            << "total " << MiB << " MiB (" << bytes << " bytes)" << std::endl
            << "in " << elapsed_seconds << " seconds (" << rate_MiBps << " MiB/s)" << std::endl;

  return EXIT_SUCCESS;
}

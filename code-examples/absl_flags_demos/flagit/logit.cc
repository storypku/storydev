#include <iostream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "glog/logging.h"

// Conflict with glog
// ABSL_FLAG(bool, logtostderr, false, "Whether log to stderr");
ABSL_FLAG(bool, enable_log, false, "Whether log to stderr");

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  // Overrides the default for FLAGS_logtostderr
  absl::SetFlag(&FLAGS_enable_log, true);
  // If the command-line contains a value for logtostderr, use that. Otherwise,
  // use the default (as set above).
  absl::ParseCommandLine(argc, argv);
  auto logtostderr = absl::GetFlag(FLAGS_enable_log);
  std::cout << (logtostderr ? "Yes, LogIt" : "Silent") << std::endl;
  LOG(INFO) << (logtostderr ? "Yes, LogIt" : "Silent") << std::endl;
  return 0;
}

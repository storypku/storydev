#include <iostream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/time/time.h"

ABSL_RETIRED_FLAG(absl::Duration, timeout, absl::Seconds(30),
                  "Default RPC deadline");

int main(int argc, char* argv[]) {
  auto remained_args = absl::ParseCommandLine(argc, argv);
  // Uncomment the following paragraph will result in compilation error:
  //    error: 'FLAGS_timeout' was not declared in this scope
  //    15 |   absl::Duration timeout = absl::GetFlag(FLAGS_timeout);
  //
  // absl::Duration timeout = absl::GetFlag(FLAGS_timeout);
  // std::cout << timeout << "\n";

  std::cout << "Remaining " << remained_args.size() << " args, they are: "
            << "\t";
  for (const auto& arg : remained_args) {
    std::cout << arg << "\n";
  }
  return 0;
}

// Running `./retired_flag --timeout=30s a b c` returns:
// ERROR: Accessing retired flag 'timeout'
// but still succeeded.

#include <iostream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/time/time.h"

ABSL_FLAG(bool, big_menu, true,
          "Include 'advanced' options in the menu listing");
ABSL_FLAG(std::string, output_dir, "foo/bar/baz/", "output file dir");
ABSL_FLAG(std::vector<std::string>, languages,
          std::vector<std::string>({"english", "french", "german"}),
          "comma-separated list of languages to offer in the 'lang' menu");
ABSL_FLAG(absl::Duration, timeout, absl::Seconds(30), "Default RPC deadline");

int main(int argc, char* argv[]) {
  auto remained_args = absl::ParseCommandLine(argc, argv);
  std::cout << (absl::GetFlag(FLAGS_big_menu) ? "Big Menu" : "No Big Menu")
            << "\n";
  std::cout << "OutputDir: " << absl::GetFlag(FLAGS_output_dir) << "\n";
  absl::Duration timeout = absl::GetFlag(FLAGS_timeout);
  // std::cout << absl::ToDoubleSeconds(timeout) << "\n";
  std::cout << timeout << "\n";
  for (const auto& lang : absl::GetFlag(FLAGS_languages)) {
    std::cout << "Lang: " << lang << "\t";
  }
  std::cout << "\n";
  std::cout << "Remaining " << remained_args.size() << " args, they are: "
            << "\t";
  for (const auto& arg : remained_args) {
    std::cout << arg << "\n";
  }
  return 0;
}

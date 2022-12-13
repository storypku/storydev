#include <iostream>

#include "gflags/gflags.h"

DEFINE_int32(answer, 42, "The answer of universe");
DEFINE_bool(verbose, false, "Whether verbose output or not");
DEFINE_string(office, "Beijing", "Office location");

int main(int argc, char* argv[]) {
  // int orig = argc;
  gflags::ParseCommandLineFlags(&argc, &argv, /*remove_flags=*/true);
  std::cout << "answer: " << FLAGS_answer << std::endl;
  std::cout << "verbose:" << std::boolalpha << FLAGS_verbose << std::endl;
  std::cout << "office:" << FLAGS_office << std::endl;
  for (int i = 0; i < argc; ++i) {
    std::cout << "Argv[" << i << "]=" << argv[i] << std::endl;
  }

  gflags::SetCommandLineOption("office", "onboard");

  std::vector<gflags::CommandLineFlagInfo> all_flags;
  gflags::GetAllFlags(&all_flags);
  for (const auto& flag : all_flags) {
    std::cout << flag.name << "=" << flag.current_value << std::endl;
  }

  auto office = gflags::GetCommandLineFlagInfoOrDie("office").current_value;
  std::cout << "Office=" << office << std::endl;
  return 0;
}

#include <iostream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"
#include "absl/strings/str_cat.h"
#include "flagit/elsewhere.h"

ABSL_FLAG(int32_t, answer, 42, "the answer to universe");

int main(int argc, char* argv[]) {
  std::string help_msg = absl::StrCat("Usage:\n  ", argv[0], " <office>");
  absl::SetProgramUsageMessage(help_msg);
  auto remained_args = absl::ParseCommandLine(argc, argv);
  argc = remained_args.size();
  if (argc != 2) {
    std::cerr << help_msg << std::endl;
    return -1;
  }
  auto orig = absl::GetFlag(FLAGS_answer);
  std::cout << "The origin answer to universe is: " << orig << std::endl;
  absl::SetFlag(&FLAGS_answer, orig + 10);
  auto latest = absl::GetFlag(FLAGS_answer);
  std::cout << "The new answer to universe is: " << latest << std::endl;
  std::cout << "Office=" << remained_args[1] << std::endl;

  bool noticed = absl::GetFlag(FLAGS_noticed);
  std::cout << (noticed ? "Noticed" : "Not noticed") << std::endl;
  return 0;
}

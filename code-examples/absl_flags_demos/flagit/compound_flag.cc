#include <iostream>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"

namespace qcraft {

struct CompoundFlag {
  std::pair<int, std::string> data;
};

bool AbslParseFlag(absl::string_view text, CompoundFlag* flag,
                   std::string* err);

std::string AbslUnparseFlag(const CompoundFlag&);

// Within the implementation, `AbslParseFlag()` will, in turn invoke
// `absl::ParseFlag()` on its constituent `int` and `std::string` types
// (which have built-in Abseil flag support.

bool AbslParseFlag(absl::string_view text, CompoundFlag* flag,
                   std::string* err) {
  std::pair<absl::string_view, absl::string_view> tokens =
      absl::StrSplit(text, ',');
  if (!absl::ParseFlag(tokens.first, &flag->data.first, err)) return false;
  if (!absl::ParseFlag(tokens.second, &flag->data.second, err)) return false;
  return true;
}

// Similarly, for unparsing, we can simply invoke `absl::UnparseFlag()` on
// the constituent types.
std::string AbslUnparseFlag(const CompoundFlag& flag) {
  return absl::StrCat(absl::UnparseFlag(flag.data.first), ",",
                      absl::UnparseFlag(flag.data.second));
}
}  // namespace qcraft

ABSL_FLAG(qcraft::CompoundFlag, myflag, qcraft::CompoundFlag(),
          "Compound flag that controls sth.");

int main(int argc, char* argv[]) {
  absl::ParseCommandLine(argc, argv);
  auto myflag = absl::GetFlag(FLAGS_myflag);
  std::cout << "--myflag=" << qcraft::AbslUnparseFlag(myflag) << std::endl;
  return 0;
}

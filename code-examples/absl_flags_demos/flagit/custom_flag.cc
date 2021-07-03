#include <iostream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_cat.h"

namespace qcraft {

enum class OutputMode { kPlainText, kHtml };

// AbslParseFlag converts from a string to OutputMode.
// Must be in same namespace as OutputMode.

// Parses an OutputMode from the command line flag value `text`. Returns
// `true` and sets `*mode` on success; returns `false` and sets `*error`
// on failure.
bool AbslParseFlag(absl::string_view text, OutputMode* mode,
                   std::string* error) {
  if (text == "plaintext") {
    *mode = OutputMode::kPlainText;
    return true;
  }
  if (text == "html") {
    *mode = OutputMode::kHtml;
    return true;
  }
  *error = "unknown value for enumeration";
  return false;
}

// AbslUnparseFlag converts from an OutputMode to a string.
// Must be in same namespace as OutputMode.

// Returns a textual flag value corresponding to the OutputMode `mode`.
std::string AbslUnparseFlag(OutputMode mode) {
  switch (mode) {
    case OutputMode::kPlainText:
      return "plaintext";
    case OutputMode::kHtml:
      return "html";
    default:
      return absl::StrCat(mode);
  }
}

}  // namespace qcraft

ABSL_FLAG(qcraft::OutputMode, output, qcraft::OutputMode::kPlainText,
          "Output mode");

int main(int argc, char* argv[]) {
  absl::ParseCommandLine(argc, argv);
  auto output = absl::GetFlag(FLAGS_output);
  std::cout << absl::StrCat(output) << std::endl;
  std::cout << qcraft::AbslUnparseFlag(output) << std::endl;
  return 0;
}

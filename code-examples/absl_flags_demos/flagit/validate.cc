#include <iostream>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/marshalling.h"
#include "absl/flags/parse.h"
#include "absl/strings/string_view.h"

struct PortNumber {
  explicit PortNumber(int p = 0) : port(p) {}

  int port;  // Valid range is [0..32767]
};

// Returns a textual flag value corresponding to the PortNumber `p`.
std::string AbslUnparseFlag(PortNumber p) {
  // Delegate to the usual unparsing for int.
  return absl::UnparseFlag(p.port);
}

// Parses a PortNumber from the command line flag value `text`.
// Returns true and sets `*p` on success; returns false and sets `*error`
// on failure.
bool AbslParseFlag(absl::string_view text, PortNumber* p, std::string* error) {
  // Convert from text to int using the int-flag parser.
  if (!absl::ParseFlag(text, &p->port, error)) {
    return false;
  }
  if (p->port < 0 || p->port > 32767) {
    *error = "not in range [0,32767]";
    return false;
  }
  return true;
}

ABSL_FLAG(PortNumber, port, PortNumber(0), "What port to listen on");

int main(int argc, char* argv[]) {
  absl::ParseCommandLine(argc, argv);
  auto port = absl::GetFlag(FLAGS_port);
  std::cout << "Port: " << port.port << std::endl;
  return 0;
}

// -- --port=10086

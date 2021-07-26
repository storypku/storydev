#include "onboard/utils/file_util.h"
namespace qcraft {

std::string GetFileExtension(std::string_view filename) {
  const auto pos = filename.rfind(".");
  if (pos == std::string_view::npos) {
    return std::string();
  } else {
    // E.g., 1) a.txt => txt 2) a.pb.txt => txt
    return filename.substr(pos + 1).data();
  }
}

}  // namespace qcraft

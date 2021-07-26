#pragma once

#include <string>
#include <string_view>

namespace qcraft {

// Get file extension based on filename
std::string GetFileExtension(std::string_view filename);

}  // namespace qcraft

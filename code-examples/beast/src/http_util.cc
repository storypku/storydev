#include "src/http_util.h"

#include "onboard/utils/file_util.h"

namespace qcraft {
namespace net {
namespace http {

beast::string_view mime_type(beast::string_view path) {
  auto ext = ::qcraft::GetFileExtension(path.data());
  if (ext == "htm" || ext == "html" || ext == "php") {
    return "text/html";
  } else if (ext == "css") {
    return "text/css";
  } else if (ext == "txt") {
    return "text/plain";
  } else if (ext == "js") {
    return "application/javascript";
  } else if (ext == "json") {
    return "application/json";
  } else if (ext == "xml") {
    return "application/xml";
  } else if (ext == "swf") {
    return "application/x-shockwave-flash";
  } else if (ext == "flv") {
    return "video/x-flv";
  } else if (ext == "png") {
    return "image/png";
  } else if (ext == "jpe" || ext == "jpeg" || ext == "jpg") {
    return "image/jpeg";
  } else if (ext == "gif") {
    return "image/gif";
  } else if (ext == "bmp") {
    return "image/bmp";
  } else if (ext == "ico") {
    return "image/vnd.microsoft.icon";
  } else if (ext == "tiff" || ext == "tif") {
    return "image/tiff";
  } else if (ext == "svg") {
    return "image/svg+xml";
  } else if (ext == "svgz") {
    return "image/svg+xml";
  }
  return "application/text";
}

}  // namespace http
}  // namespace net
}  // namespace qcraft

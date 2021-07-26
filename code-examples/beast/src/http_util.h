#pragma once

#include <string_view>

#include "boost/asio.hpp"
// #include "boost/asio/ip/tcp.hpp"
#include "boost/beast.hpp"
#include "boost/beast/http.hpp"
#include "boost/beast/websocket.hpp"

namespace qcraft {
namespace net {
namespace http {

namespace beast = boost::beast;
namespace http = boost::beast::http;
namespace websocket = boost::beast::websocket;
namespace net = boost::asio;
// using tcp = boost::asio::ip::tcp;

// Return a reasonable mime type based on the extension of a file.
beast::string_view mime_type(beast::string_view path);

}  // namespace http
}  // namespace net
}  // namespace qcraft

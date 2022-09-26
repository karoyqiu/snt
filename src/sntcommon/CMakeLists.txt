find_package(Flatbuffers CONFIG REQUIRED)

include("BuildFlatBuffers")
flatbuffers_generate_headers(
  TARGET sntfbs
  SCHEMAS "sntcommon.fbs" "sntrequest.fbs" "sntresponse.fbs"
)

add_library(sntcommon
  "messages.h" "messages.cpp"
  "keyed_logger.h"
)
target_compile_options(sntcommon PUBLIC ${PROJECT_WARNING_FLAGS})
target_precompile_headers(sntcommon PUBLIC
  "<asio.hpp>"
  "<boost/predef.h>"
  "<flatbuffers/flatbuffers.h>"
  "<spdlog/spdlog.h>"
  "<yaml-cpp/yaml.h>"
)
target_include_directories(sntcommon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sntcommon PUBLIC
  flatbuffers::flatbuffers
  spdlog::spdlog spdlog::spdlog_header_only
  OpenSSL::Crypto
  sntfbs
)

if(WIN32)
  target_compile_definitions(sntcommon PUBLIC "_WIN32_WINNT=0x0601")
endif()

include(GenerateExportHeader)

add_library(sntcommon
  "messages.h" 
  "keyed_logger.h"
 "crypto_random.h" "crypto_random.cpp" "nanoid.h" "nanoid.cpp")
generate_export_header(sntcommon)
target_compile_options(sntcommon PUBLIC ${PROJECT_WARNING_FLAGS})
target_precompile_headers(sntcommon PUBLIC
  "<spdlog/spdlog.h>"
  "<yaml-cpp/yaml.h>"
  "<RCF/RCF.hpp>"
)
target_include_directories(sntcommon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(sntcommon PUBLIC
  rcf
  spdlog::spdlog spdlog::spdlog_header_only
)

if(WIN32)
  target_compile_definitions(sntcommon PUBLIC "_WIN32_WINNT=0x0601" "WIN32_LEAN_AND_MEAN")
endif()

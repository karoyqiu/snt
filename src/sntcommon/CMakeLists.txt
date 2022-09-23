add_library(sntcommon
    "messages.h" "messages.cpp"
)
target_compile_options(sntcommon PUBLIC ${PROJECT_WARNING_FLAGS})
target_include_directories(sntcommon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sntcommon PUBLIC OpenSSL::Crypto)

if(WIN32)
    target_compile_definitions(sntcommon PUBLIC "_WIN32_WINNT=0x0601")
endif()

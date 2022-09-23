add_executable(sntc
    "main.cpp"
    "client.h" "client.cpp"
)

target_precompile_headers(sntc PRIVATE "stable.h")
target_link_libraries(sntc PRIVATE
    asio asio::asio
    OpenSSL::SSL OpenSSL::Crypto
    yaml-cpp
    sntcommon
)

target_compile_definitions(sntc PRIVATE
    "ASIO_NO_DEPRECATED"
    "ASIO_NO_TS_EXECUTORS"
    "ASIO_NO_DYNAMIC_BUFFER_V1"
    "ASIO_NO_TYPEID"
)

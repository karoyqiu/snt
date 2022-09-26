add_executable(sntd
  "main.cpp"
  "server.h" "server.cpp"
  "session.h" "session.cpp"
  "listen_session.h" "listen_session.cpp"
)

target_link_libraries(sntd PRIVATE
  asio asio::asio
  OpenSSL::SSL OpenSSL::Crypto
  yaml-cpp
  sntcommon
)

target_compile_definitions(sntd PRIVATE
  "ASIO_NO_DEPRECATED"
  "ASIO_NO_TS_EXECUTORS"
  "ASIO_NO_DYNAMIC_BUFFER_V1"
  "ASIO_NO_TYPEID"
)

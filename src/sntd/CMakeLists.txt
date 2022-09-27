add_executable(sntd
  "main.cpp"
  "server.h" "server.cpp"
  "session.h" "session.cpp"
  "listen_session.h" "listen_session.cpp"
)

target_link_libraries(sntd PRIVATE
  yaml-cpp
  sntcommon
)

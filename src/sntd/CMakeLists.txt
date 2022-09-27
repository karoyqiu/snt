add_executable(sntd
  "main.cpp"
  "service.h" "service.cpp"
  #"session.h" "session.cpp"
  #"listen_session.h" "listen_session.cpp"
 "session.h")

target_link_libraries(sntd PRIVATE
  yaml-cpp
  sntcommon
)

add_executable(sntd
  "main.cpp"
  "service.h" "service.cpp"
  "session.h"
  "listener.h" "listener.cpp"
  "connect_session.h "connect_session.cpp""
 "session_manager.h")

target_link_libraries(sntd PRIVATE
  yaml-cpp
  sntcommon
)

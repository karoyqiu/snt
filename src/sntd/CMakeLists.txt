add_executable(sntd
  "main.cpp"
  "service.h" "service.cpp"
  "session.h" "session_manager.h"
  "listener.h" "listener.cpp"
  "connect_session.h" "connect_session.cpp"
)

target_link_libraries(sntd PRIVATE
  yaml-cpp
  sntcommon
)

add_executable(sntd
  "main.cpp"
  "service.h" "service.cpp"
  "session.h"
  "listen_session.h" "listen_session.cpp"
)

target_link_libraries(sntd PRIVATE
  yaml-cpp
  sntcommon
)

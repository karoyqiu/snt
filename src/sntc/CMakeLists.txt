add_executable(sntc
  "main.cpp"
  "client.h" "client.cpp"
  "remote_session.h" "remote_session.cpp"
 "sntd.h" "sntd.cpp")

target_link_libraries(sntc PRIVATE
  yaml-cpp
  sntcommon
)

install(TARGETS sntc)

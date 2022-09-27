add_executable(sntc
  "main.cpp"
  "client.h" "client.cpp"
)

target_link_libraries(sntc PRIVATE
  yaml-cpp
  sntcommon
)

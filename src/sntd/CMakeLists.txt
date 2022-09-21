add_executable(sntd
    "main.cpp"
    "server.h" "server.cpp"
    "session.h" "session.cpp"
)

target_precompile_headers(sntd PRIVATE "stable.h")
target_link_libraries(sntd PRIVATE
    asio asio::asio
    OpenSSL::SSL OpenSSL::Crypto
)

target_compile_options(sntd PRIVATE ${PROJECT_WARNING_FLAGS})

if(WIN32)
    target_compile_definitions(sntd PRIVATE "_WIN32_WINNT=0x0601")
endif()

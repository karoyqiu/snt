# 编译 RCF
add_library(rcf "src/RCF/RCF.cpp")

if(BUILD_SHARED_LIBS)
  target_compile_definitions(rcf PRIVATE "RCF_BUILD_DLL")
endif()

target_compile_definitions(rcf PRIVATE
  "RCF_FEATURE_SSPI=0"
  "RCF_FEATURE_PUBSUB=0"
  "RCF_FEATURE_NAMEDPIPE=0"
  "RCF_FEATURE_LOCALSOCKET=0"
  "RCF_FEATURE_HTTP=0"
  "RCF_FEATURE_OPENSSL=1"
)

if(WIN32)
  target_compile_definitions(rcf PRIVATE "_WIN32_WINNT=0x0601")
elseif(UNIX)
  find_package(unofficial-libuuid CONFIG REQUIRED)
  target_link_libraries(rcf PRIVATE unofficial::UUID::uuid)
endif()

target_include_directories(rcf PUBLIC "include")
target_link_libraries(rcf PUBLIC OpenSSL::SSL OpenSSL::Crypto)

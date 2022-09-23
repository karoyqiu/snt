#*! ***********************************************************************************************
#
# \file        CMakeLists.txt
# \brief       snt 主 CMakeLists。
#
# \version     0.1
# \date        2022/9/21
#
# \author      Roy QIU <karoyqiu@gmail.com>
# \copyright   © 2022 Roy QIU。
#
#*************************************************************************************************/
cmake_minimum_required(VERSION 3.23)

# 设置全局变量
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_C_VISIBILITY_PRESET "hidden")
set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#set(CMAKE_USER_MAKE_RULES_OVERRIDE_C    ${CMAKE_SOURCE_DIR}/cmake/CFlagOverrides.cmake)
#set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX  ${CMAKE_SOURCE_DIR}/cmake/CXXFlagOverrides.cmake)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_SKIP_BUILD_RPATH OFF)
set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)

set(CMAKE_BUILD_TYPE Debug CACHE STRING
    "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel.")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)

# Project snt
project(snt VERSION 0.0.1)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# 检查是否支持 IPO
include(CheckIPOSupported OPTIONAL)
if(COMMAND check_ipo_supported)
    check_ipo_supported(RESULT PROJECT_IS_IPO_SUPPORTED)

    if(PROJECT_IS_IPO_SUPPORTED)
        option(PROJECT_ENABLE_IPO "Enable IPO for non-debug build." OFF)
    endif()
endif()

if(PROJECT_ENABLE_IPO)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL ON)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO ON)
else()
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL OFF)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE OFF)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO OFF)
endif()

# 判断目标架构
#include(TargetArch)
#target_architecture(PROJECT_TARGET_ARCH)

# 检查编译器警告选项
include(WarningFlags)
check_warning_flags(PROJECT_WARNING_FLAGS)

# 第三方库
find_package(asio REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

#include(EnableFolder)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 源代码
add_subdirectory("src")

# 打包，提前设置供安装库使用。
# set(CPACK_PACKAGE_NAME "${PROJECT_NAME}-all")
# set(CPACK_PACKAGE_VENDOR "karoyqiu@gmail.com")
# set(CPACK_PACKAGE_CONTACT "karoyqiu@gmail.com")
# set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
# set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
# set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
# set(CPACK_PACKAGE_CHECKSUM SHA256)
# set(CPACK_VERBATIM_VARIABLES ON)
# set(CPACK_STRIP_FILES ON)
# set(CPACK_GENERATOR "ZIP")
# include(CPack)

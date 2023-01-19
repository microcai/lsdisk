cmake_minimum_required(VERSION 3.0)
project(smartsock5)

cmake_policy(SET CMP0058 NEW)
include(CheckCXXCompilerFlag)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(STATIC_EXE "static link" OFF)

if(MSVC)
set (CMAKE_CONFIGURATION_TYPES "Release;Debug")
set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_RELEASE
   )

foreach(CompilerFlag ${CompilerFlags})
  string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()

foreach(CompilerFlag ${CompilerFlags})
  string(REPLACE "/W3" "/W1" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8 /bigobj /MP")

#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}  /ignore:4099 /NODEFAULTLIB:libcmt.lib ")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER}  /SAFESEH:NO ")
else()
check_cxx_compiler_flag(-std=c++17 HAS_CXX17)
if (HAS_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")
endif()
endif(MSVC)

if (STATIC_EXE)
	set(CMAKE_CXX_FLAGS "-static -static-libgcc")
endif()

find_package(Threads)

link_libraries(${CMAKE_THREAD_LIBS_INITD})

if(WIN32)
	add_definitions(-DBOOST_ALL_STATIC_LINK -DBOOST_AUTO_LINK_NOMANGLE)
	add_definitions(-DBOOST_THREAD_USE_LIB)
	add_definitions(-DBOOST_FILESYSTEM_STATIC_LINK)
	add_definitions(-DWIN32_LEAN_AND_MEAN)
	add_definitions(-DNOMINMAX)
endif()

find_package(Boost 1.81 REQUIRED COMPONENTS filesystem regex)

##################
# real project stuff
##################
add_subdirectory(src)

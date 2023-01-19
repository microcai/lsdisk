
include(CheckIncludeFile)

include(CheckSymbolExists)

CHECK_SYMBOL_EXISTS(MSG_DONTWAIT "sys/socket.h" HAVE_MSG_DONTWAIT)
if (HAVE_MSG_DONTWAIT)
	add_definitions(-DHAVE_MSG_DONTWAIT)
endif()

add_definitions(-DBOOST_ASIO_NO_DEPRECATED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_executable(lssas lssas.cpp)

target_link_libraries(lssas Boost::filesystem Boost::regex)

install(TARGETS lssas DESTINATION bin)

add_executable(lsnvme lsnvme.cpp)

target_link_libraries(lsnvme Boost::filesystem Boost::regex)

install(TARGETS lsnvme DESTINATION bin)
cmake_minimum_required(VERSION 3.14)
project(data_access)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_CXX_STANDARD 17)

#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})

find_package(fmt)
include_directories(${fmt_INCLUDE_DIRS})

set(HEADER_FILES
#        mock/CoordRepository.h
#        mock/ImageRepository.h
#        mock/MarkedObjectRepository.h
#        mock/MarkRepository.h
#        mock/UserRepository.h
        mock_repository/ImageRepository.h
        mock_repository/MarkedObjectRepository.h
        mock_repository/MarkRepository.h
        mock_repository/UserRepository.h
        psql_repository/PSQLImageRepository.h
        psql_repository/PSQLMarkedObjectRepository.h
        psql_repository/PSQLMarkRepository.h
        psql_repository/PSQLUserRepository.h
        psql_repository/Query.h)

set(SOURCE_FILES
#        mock/CoordRepository.cpp
#        mock/ImageRepository.cpp
#        mock/MarkedObjectRepository.cpp
#        mock/MarkRepository.cpp
#        mock/UserRepository.cpp
        mock_repository/ImageRepository.cpp
        mock_repository/MarkedObjectRepository.cpp
        mock_repository/MarkRepository.cpp
        mock_repository/UserRepository.cpp
        psql_repository/PSQLImageRepository.cpp
        psql_repository/PSQLMarkedObjectRepository.cpp
        psql_repository/PSQLMarkRepository.cpp
        psql_repository/PSQLUserRepository.cpp
        psql_repository/Query.cpp)

add_library(data_access SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(data_access business_logic fmt::fmt)
#target_link_libraries(data_access ${OpenCV_LIBS})
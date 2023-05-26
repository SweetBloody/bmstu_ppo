cmake_minimum_required(VERSION 3.14)
project(business_logic)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} exception logger managers objects repository_interface)

set(HEADER_FILES
        exception/Exception.h
        repository_interface/IImageRepository.h
        repository_interface/IMarkedObjectRepository.h
        repository_interface/IMarkRepository.h
        repository_interface/IUserRepository.h
        objects/image/Image.h
        objects/marked_object/MarkedObject.h
        objects/mark/Mark.h
        objects/user/User.h
        objects/dot/Dot.h
        managers/AccountManager.h
        managers/ImageManager.h
        managers/LabelingManager.h
        managers/DataFileManager.h
        managers/MarkManager.h)

set(SOURCE_FILES
        managers/AccountManager.cpp
        managers/ImageManager.cpp
        managers/LabelingManager.cpp
        managers/DataFileManager.cpp
        objects/image/Image.cpp
        objects/marked_object/MarkedObject.cpp
        objects/mark/Mark.cpp
        objects/user/User.cpp
        managers/MarkManager.cpp
        objects/connection/Connection.cpp
        objects/connection/Connection.h
        logger/Logger.cpp
        logger/Logger.h)

add_library(business_logic SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(business_logic ${OpenCV_LIBS} -lpqxx -lpq)
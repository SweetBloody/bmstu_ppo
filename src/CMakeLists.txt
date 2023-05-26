#cmake_minimum_required(VERSION 3.14)
#project(src)
#
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#
#set(CMAKE_CXX_STANDARD 17)
#
#
#find_package(OpenCV REQUIRED)
##find_package(GTest CONFIG REQUIRED)
#
#include_directories(${OpenCV_INCLUDE_DIRS},
##        ${GTEST_INCLUDE_DIRS},
#        tests,
#                    data_access,
#                    business_logic,
#                    business_logic/objects,
#                    data_access/mock_repository,
#                    business_logic/managers,
#                    business_logic/repository_interface)
#
#message(${CMAKE_CURRENT_SOURCE_DIR})
#
#add_executable(src main.cpp
#        business_logic/managers/AccountManager.cpp
##        business_logic/managers/AccountManager.h
#        business_logic/managers/ImageManager.cpp
##        business_logic/managers/image_manager.h
#        business_logic/managers/LabelingManager.cpp
##        business_logic/managers/marking_manager.h
#        business_logic/managers/DataFileManager.cpp
##        business_logic/managers/data_file_manager.h
#        business_logic/objects/image/Image.cpp
##        business_logic/objects/image.h
#        business_logic/objects/marked_object/MarkedObject.cpp
##        business_logic/objects/marked_object.h
#        business_logic/objects/data_file.cpp
##        business_logic/objects/data_file.h
#        business_logic/objects/mark/Mark.cpp
##        business_logic/objects/mark.h
#        business_logic/objects/user/User.cpp
#        business_logic/objects/user/User.h
#        business_logic/objects/admin.cpp
##        business_logic/objects/admin.h
#        data_access/mock_repository/UserRepository.cpp
#        data_access/mock_repository/UserRepository.h business_logic/repository_interface/IImageRepository.h data_access/mock_repository/ImageRepository.cpp data_access/mock_repository/ImageRepository.h business_logic/objects/dot/Dot.cpp business_logic/objects/dot/Dot.h business_logic/objects/marked_object/circle_marked_object/CircleMarkedObject.cpp business_logic/objects/marked_object/circle_marked_object/CircleMarkedObject.h business_logic/objects/marked_object/polygon_marked_object/PolygonMarkedObject.cpp business_logic/objects/marked_object/polygon_marked_object/PolygonMarkedObject.h business_logic/repository_interface/IMarkedObjectRepository.h business_logic/repository_interface/IMarkRepository.h business_logic/repository_interface/ICoordRepository.h data_access/mock_repository/MarkedObjectRepository.cpp data_access/mock_repository/MarkedObjectRepository.h data_access/mock_repository/MarkRepository.cpp data_access/mock_repository/MarkRepository.h business_logic/managers/MarkManager.cpp business_logic/managers/MarkManager.h business_logic/exception/Exception.cpp business_logic/exception/Exception.h data_access/mock_repository/CoordRepository.cpp data_access/mock_repository/CoordRepository.h tests/Test.cpp tests/Test.h)
##        business_logic/repository_interface/IUserRepository.h)
#
#target_link_libraries(src ${OpenCV_LIBS})
##target_link_libraries(src ${GTEST_LIBRARIES} pthread)
#
#add_subdirectory(tests)



#----------------------------------------

cmake_minimum_required(VERSION 3.14)
project(src)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")


#set(SOURCE_FILES tech_ui/tech_main.cpp)
set(SOURCE_FILES main.cpp)
add_executable(src_run ${SOURCE_FILES})

include_directories(business_logic)
add_subdirectory(business_logic)

include_directories(data_access)
add_subdirectory(data_access)

include_directories(tech_ui)
add_subdirectory(tech_ui)

#include_directories(tests)
#add_subdirectory(tests)

target_link_libraries(src_run business_logic data_access tech_ui)

# -------------------------------------------
#target_link_libraries(src_run data_access)

#add_subdirectory(tests)
#find_package(OpenCV REQUIRED)
#find_package(GTest CONFIG REQUIRED)

#include_directories(${OpenCV_INCLUDE_DIRS},
#        #        ${GTEST_INCLUDE_DIRS},
#        tests,
#        data_access,
#        business_logic,
#        business_logic/objects,
#        data_access/mock_repository,
#        business_logic/managers,
#        business_logic/repository_interface)
#
#message(${CMAKE_CURRENT_SOURCE_DIR})
#
#add_executable(src main.cpp
#        business_logic/managers/AccountManager.cpp
#        #        business_logic/managers/AccountManager.h
#        business_logic/managers/ImageManager.cpp
#        #        business_logic/managers/image_manager.h
#        business_logic/managers/LabelingManager.cpp
#        #        business_logic/managers/marking_manager.h
#        business_logic/managers/DataFileManager.cpp
#        #        business_logic/managers/data_file_manager.h
#        business_logic/objects/image/Image.cpp
#        #        business_logic/objects/image.h
#        business_logic/objects/marked_object/MarkedObject.cpp
#        #        business_logic/objects/marked_object.h
#        business_logic/objects/data_file.cpp
#        #        business_logic/objects/data_file.h
#        business_logic/objects/mark/Mark.cpp
#        #        business_logic/objects/mark.h
#        business_logic/objects/user/User.cpp
#        business_logic/objects/user/User.h
#        business_logic/objects/admin.cpp
#        #        business_logic/objects/admin.h
#        data_access/mock_repository/UserRepository.cpp
#        data_access/mock_repository/UserRepository.h business_logic/repository_interface/IImageRepository.h data_access/mock_repository/ImageRepository.cpp data_access/mock_repository/ImageRepository.h business_logic/objects/dot/Dot.cpp business_logic/objects/dot/Dot.h business_logic/objects/marked_object/circle_marked_object/CircleMarkedObject.cpp business_logic/objects/marked_object/circle_marked_object/CircleMarkedObject.h business_logic/objects/marked_object/polygon_marked_object/PolygonMarkedObject.cpp business_logic/objects/marked_object/polygon_marked_object/PolygonMarkedObject.h business_logic/repository_interface/IMarkedObjectRepository.h business_logic/repository_interface/IMarkRepository.h business_logic/repository_interface/ICoordRepository.h data_access/mock_repository/MarkedObjectRepository.cpp data_access/mock_repository/MarkedObjectRepository.h data_access/mock_repository/MarkRepository.cpp data_access/mock_repository/MarkRepository.h business_logic/managers/MarkManager.cpp business_logic/managers/MarkManager.h business_logic/exception/Exception.cpp business_logic/exception/Exception.h data_access/mock_repository/CoordRepository.cpp data_access/mock_repository/CoordRepository.h tests/Test.cpp tests/Test.h)
##        business_logic/repository_interface/IUserRepository.h)
#
#target_link_libraries(src ${OpenCV_LIBS})
##target_link_libraries(src ${GTEST_LIBRARIES} pthread)
#
#add_subdirectory(tests)
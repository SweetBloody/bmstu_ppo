cmake_minimum_required(VERSION 3.14)
project(tech_ui)
set(CMAKE_CXX_STANDARD 17)

include_directories(app config_reader controller request)

set(HEADER_FILES
        app/App.h
        request/Request.h
        state/State.h
        controller/Controller.h)

set(SOURCE_FILES
        app/App.cpp
        request/Request.cpp
        state/State.cpp
        controller/Controller.cpp config_reader/ConfigReader.h config_reader/json.hpp)

add_library(tech_ui SHARED ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(tech_ui business_logic data_access)
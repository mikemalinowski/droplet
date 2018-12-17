cmake_minimum_required(VERSION 3.3)
project(droplet)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/Auxillary/AuxMath.h
        src/Core/droplet.cpp
        src/Core/droplet.h
        src/Nodes/Utility/FloatOpCompound.cpp
        src/Nodes/Utility/FloatOpCompound.h
        src/Nodes/Rigging/QuaternionTwist.cpp
        src/Nodes/Rigging/QuaternionTwist.h
        src/Nodes/Rigging/Soft2BoneIk.cpp
        src/Nodes/Rigging/Soft2BoneIk.h)

find_package(Maya REQUIRED)

add_library(droplet SHARED ${SOURCE_FILES})
target_link_libraries(droplet PRIVATE Maya::Maya)
target_include_directories(droplet PRIVATE Maya::Maya)
set_target_properties(droplet PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin/${MAYA_VERSION})

MAYA_PLUGIN(droplet)


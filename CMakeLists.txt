cmake_minimum_required(VERSION 3.3)
project(droplet)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/Utilities/Math.h
        src/Core/Registration.cpp
        src/Core/Registration.h
        src/Nodes/Utility/FloatOpCompound.cpp
        src/Nodes/Utility/FloatOpCompound.h
        src/Nodes/Rigging/QuaternionTwist.cpp
        src/Nodes/Rigging/QuaternionTwist.h
        src/Nodes/Rigging/Soft2BoneIk.cpp
        src/Nodes/Rigging/Soft2BoneIk.h
        src/Utilities/Attributes.h
        src/Nodes/Stacks/FloatStackSum.h
        src/Nodes/Stacks/FloatStackMin.h
        src/Nodes/Stacks/FloatStackMax.h
        src/Nodes/Stacks/FloatStackRange.h
        src/Nodes/Stacks/FloatStackMultiply.h
        src/Nodes/Stacks/FloatStackMinus.h
        src/Nodes/Stacks/FloatStackDivide.h
        src/Nodes/Stacks/AngleStackDivide.h
        src/Nodes/Stacks/AngleStackMax.h
        src/Nodes/Stacks/AngleStackMin.h
        src/Nodes/Stacks/AngleStackMinus.h
        src/Nodes/Stacks/AngleStackMultiply.h
        src/Nodes/Stacks/AngleStackRange.h
        src/Nodes/Stacks/AngleStackSum.h
        src/Nodes/Vectors/FloatVectorScale.h
        src/Nodes/Vectors/AngleVectorScale.h
        src/Nodes/Vectors/FloatVectorAdd.h
        src/Nodes/Vectors/FloatVectorDivide.h
        src/Nodes/Vectors/AngleVectorAdd.h
        src/Nodes/Vectors/AngleVectorDivide.h
        src/Nodes/Interpolation/InterpolateFloats.h
        src/Nodes/Interpolation/InterpolateFloatVectors.h
        src/Nodes/Interpolation/InterpolateAngles.h
        src/Nodes/Interpolation/InterpolateAngleVectors.h
        src/Nodes/Interpolation/InterpolateMatrices.h
        src/Nodes/Interpolation/InterpolateQuaternions.h
        src/Nodes/Spaces/DistanceBetweenVectors.h
        src/Nodes/Spaces/DistanceBetweenMatrices.h
        src/Nodes/Spaces/RelativeMatrix.h
        src/Nodes/Angles/AngleAdd.h
        src/Nodes/Angles/AngleSubtract.h
        src/Nodes/Angles/AngleMultiply.h
        src/Nodes/Angles/AngleDivide.h
        src/Nodes/Angles/AngleRange.h
        src/Nodes/Angles/AngleClamp.h
        src/Nodes/Angles/AngleSqrt.h
        src/Nodes/Basic/Sqrt.h
        src/Nodes/Basic/Power.h
        src/Nodes/Angles/AnglePower.h
        src/Nodes/Angles/AngleExponent.h
        src/Nodes/Basic/Exponent.h
        src/Nodes/Stacks/FloatStackSum.cpp
        src/Core/DropletNode.h)

find_package(Maya REQUIRED)

add_library(droplet SHARED ${SOURCE_FILES})
target_link_libraries(droplet PRIVATE Maya::Maya)
target_include_directories(droplet PRIVATE Maya::Maya)
set_target_properties(droplet PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin/${MAYA_VERSION})

MAYA_PLUGIN(droplet)

